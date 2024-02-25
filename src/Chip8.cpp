#include "../include/Chip8.hpp"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <chrono>
#include <random>

const unsigned int START_ADDRESS = 0x200;

const unsigned int FONTSET_SIZE = 80;

const unsigned int FONTSET_START_ADDRESS = 0x50;

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() {
    randGen.seed(std::chrono::system_clock::now().time_since_epoch().count());

    pc = START_ADDRESS;

    for(unsigned int i = 0; i < FONTSET_SIZE; ++i) {
        memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }

    // Initialize RNG
	randByte = std::uniform_int_distribution<uint8_t>(0, 255U);

}

void Chip8::LoadROM(char const* filename) {

    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if(file.is_open()) {

        // Open the file as a stream of binary and move the file pointer to the end
        std::streampos size = file.tellg();
        char* buffer = new char[size];

        // Go back to the beginning of the file and fill the buffer
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        // Load the ROM contents into the Chip8's memory, starting at 0x200
        for(long i = 0; i < size; i++) {
            memory[START_ADDRESS + i] = buffer[i];
        }

        // Free the buffer
        delete[] buffer;
    }
}

// Does nothing
void Chip8::OP_NULL(){

}

// CLS (Clear display)
void Chip8::OP_00E0(){
    std::memset(video, 0, sizeof(video));
}

// RET (return from subroutine)
void Chip8::OP_00EE(){
    sp--;
    pc = stack[sp];
}

// SYS addr (jump to machine code at nnn)
void Chip8::OP_0nnn(){

}

// JP (jump to location nnn)
void Chip8::OP_1nnn(){
    uint16_t address = opcode * 0x0FFFu;

    pc = address;
} 

// CALL addr (call subroutine at nnn)
void Chip8::OP_2nnn(){
    uint16_t address = opcode * 0x0FFFu;
    stack[sp] = pc;
    ++sp;
    pc = address;
}

// SE Vx, byte (skip next instruction if Vx = kk)
void Chip8::OP_3xkk(){
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    if(registers[Vx] == byte) {
        pc += 2;
    }
}

// SNE Vx, byte (Skip next instruction if Vx != kk)
void Chip8::OP_4xkk(){
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    if(registers[Vx] != byte) {
        pc += 2;
    }

}

// SE Vx, Vy (Skip next instruction if Vx = Vy)
void Chip8::OP_5xy0(){
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if(registers[Vx] == registers[Vy]) {
        pc += 2;
    }

}

// LD Vx, byte (Set Vx = kk)
void Chip8::OP_6xkk(){
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;
    
    registers[Vx] = byte;
}

// ADD Vx, byte (Set Vx = Vx + kk)
void Chip8::OP_7xkk(){
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;
    
    registers[Vx] += byte;
}

// LD Vx, Vy (Set Vx = Vy)
void Chip8::OP_8xy0(){
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] = registers[Vy];
}

// OR Vx, Vy (Set Vx = Vx OR Vy)
void Chip8::OP_8xy1(){
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] |= registers[Vy];
}

// AND Vx, Vy (Set Vx = Vx AND Vy)
void Chip8::OP_8xy2(){
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] &= registers[Vy];
}

// XOR Vx, Vy (Set Vx = Vx XOR Vy)
void Chip8::OP_8xy3(){
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] ^= registers[Vy];
}

// ADD Vx, Vy (Set Vx = Vx + Vy, set VF = carry)
void Chip8::OP_8xy4(){

}
// SUB Vx, Vy (Set Vx = Vx - Vy, set VF = NOT borrow)
void Chip8::OP_8xy5(){

}
// SHR Vx {, Vy} (Set Vx = Vx SHR 1)
void Chip8::OP_8xy6(){

}
// SUBN Vx, Vy (Set Vx = Vy - Vx, set VF = NOT borrow)
void Chip8::OP_8xy7(){

}
// SHL Vx {, Vy} (Set Vx = Vx SHL 1)
void Chip8::OP_8xyE(){

}
// SNE Vx, Vy (Skip next instruction if Vx != Vy)
void Chip8::OP_9xy0(){

}
// LD I, addr (Set I = nnn)
void Chip8::OP_Annn(){

}
// JP V0, addr (Jump to location nnn + V0)
void Chip8::OP_Bnnn(){

}
// RND Vx, byte (Set Vx = random byte AND kk)
void Chip8::OP_Cxkk(){

}
// DRW Vx, Vy, nibble (Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision)
void Chip8::OP_Dxyn(){

}
// SKP Vx (Skip next instruction if key with the value of Vx is pressed)
void Chip8::OP_Ex9E(){

}
// SKNP Vx (Skip next instruction if key with the value of Vx is not pressed)
void Chip8::OP_ExA1(){

}
// LD Vx, DT (Set Vx = delay timer value)
void Chip8::OP_Fx07(){

}
// LD Vx, K (Wait for a key press, store the value of the key in Vx)
void Chip8::OP_Fx0A(){

}
// LD DT, Vx (Set delay timer = Vx)
void Chip8::OP_Fx15(){

}
// LD ST, Vx (Set sound timer = Vx)
void Chip8::OP_Fx18(){

}
// ADD I, Vx (Set I = I + Vx)
void Chip8::OP_Fx1E(){

}
// LD F, Vx (Set I = location of sprite for digit Vx)
void Chip8::OP_Fx29(){

}
// LD B, Vx (Store BCD representation of Vx in memory locations I, I+1, and I+2)
void Chip8::OP_Fx33(){

}
// LD [I], Vx (Store registers V0 through Vx in memory starting at location I)
void Chip8::OP_Fx55(){

}
// LD Vx, [I] (Read registers V0 through Vx from memory starting at location I)
void Chip8::OP_Fx65(){

}