#pragma once

#include <cstdint>
#include <random>
#include <array>

const unsigned int KEY_COUNT = 16;
const unsigned int MEMORY_SIZE = 4096;
const unsigned int REGISTER_COUNT = 16;
const unsigned int STACK_LEVELS = 16;
const unsigned int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_WIDTH = 64;


class Chip8 {
    public:
    
        uint8_t keypad[KEY_COUNT]{};
        std::array<uint32_t, VIDEO_WIDTH * VIDEO_HEIGHT> video;
        //uint32_t video[VIDEO_WIDTH * VIDEO_HEIGHT]{};

        // Constructor
        Chip8();

        // Setters and Getters

        void SetRegisters(uint8_t[]);
        
        std::unique_ptr<uint16_t[]> getRegisters();

        template <typename T, std::size_t N>
        void SetMemory(std::array<T, N> buffer);

        std::array<uint8_t, MEMORY_SIZE> GetMemory();

        void setIndex(uint16_t);
        uint16_t getIndex();

        void setPC(uint16_t);
        uint16_t getPC();

        void SetStack(uint16_t[]);

        std::unique_ptr<uint16_t[]> GetStack();

        void setSP(uint8_t);
        uint8_t getSP();

        void setDelayTimer(uint8_t);
        uint8_t getDelayTimer();

        void setSoundTimer(uint8_t);
        uint8_t getSoundTimer();

        void setOPCODE(uint16_t);
        uint16_t getOPCODE();

        // Main Loop
        void Cycles();

        //Loads the rom into memory
        void LoadROM(char const*);

        // Function Pointer Table
        void Table0();
	    void Table8();
	    void TableE();
	    void TableF();


        // Does nothing
        void OP_NULL();

        // CLS (Clear display)
        void OP_00E0();

        // RET (return from subroutine)
        void OP_00EE();

        // SYS addr (jump to machine code at nnn)
        void OP_0nnn();

        // JP (jump to location nnn)
        void OP_1nnn(); 

        // CALL addr (call subroutine at nnn)
        void OP_2nnn();

        // SE Vx, byte (skip next instruction if Vx = kk)
        void OP_3xkk();

        // SNE Vx, byte (Skip next instruction if Vx != kk)
        void OP_4xkk();

        // SE Vx, Vy (Skip next instruction if Vx = Vy)
        void OP_5xy0();

        // LD Vx, byte (Set Vx = kk)
        void OP_6xkk();

        // ADD Vx, byte (Set Vx = Vx + kk)
        void OP_7xkk();

        // LD Vx, Vy (Set Vx = Vy)
        void OP_8xy0();

        // OR Vx, Vy (Set Vx = Vx OR Vy)
        void OP_8xy1();

        // AND Vx, Vy (Set Vx = Vx AND Vy)
        void OP_8xy2();

        // XOR Vx, Vy (Set Vx = Vx XOR Vy)
        void OP_8xy3();

        // ADD Vx, Vy (Set Vx = Vx + Vy, set VF = carry)
        void OP_8xy4();

        // SUB Vx, Vy (Set Vx = Vx - Vy, set VF = NOT borrow)
        void OP_8xy5();

        // SHR Vx {, Vy} (Set Vx = Vx SHR 1)
        void OP_8xy6();

        // SUBN Vx, Vy (Set Vx = Vy - Vx, set VF = NOT borrow)
        void OP_8xy7();

        // SHL Vx {, Vy} (Set Vx = Vx SHL 1)
        void OP_8xyE();

        // SNE Vx, Vy (Skip next instruction if Vx != Vy)
        void OP_9xy0();

        // LD I, addr (Set I = nnn)
        void OP_Annn();

        // JP V0, addr (Jump to location nnn + V0)
        void OP_Bnnn();

        // RND Vx, byte (Set Vx = random byte AND kk)
        void OP_Cxkk();

        // DRW Vx, Vy, nibble (Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision)
        void OP_Dxyn();

        // SKP Vx (Skip next instruction if key with the value of Vx is pressed)
        void OP_Ex9E();

        // SKNP Vx (Skip next instruction if key with the value of Vx is not pressed)
        void OP_ExA1();

        // LD Vx, DT (Set Vx = delay timer value)
        void OP_Fx07();

        // LD Vx, K (Wait for a key press, store the value of the key in Vx)
        void OP_Fx0A();

        // LD DT, Vx (Set delay timer = Vx)
        void OP_Fx15();

        // LD ST, Vx (Set sound timer = Vx)
        void OP_Fx18();

        // ADD I, Vx (Set I = I + Vx)
        void OP_Fx1E();

        // LD F, Vx (Set I = location of sprite for digit Vx)
        void OP_Fx29();

        // LD B, Vx (Store BCD representation of Vx in memory locations I, I+1, and I+2)
        void OP_Fx33();

        // LD [I], Vx (Store registers V0 through Vx in memory starting at location I)
        void OP_Fx55();

        // LD Vx, [I] (Read registers V0 through Vx from memory starting at location I)
        void OP_Fx65();


    private:
        // 16 8-bit registers
        uint8_t registers[REGISTER_COUNT]{};

        // 4KB of memory
        std::array<uint8_t, MEMORY_SIZE> memory;

        // 16-bit Address register only holds 12 bit because of memory restriction
        uint16_t index{};

        // Program counter
        uint16_t pc{};

        // Stack holds address to return to
        uint16_t stack[STACK_LEVELS]{};

        // Stack pointer
        uint8_t sp{};
        uint8_t delayTimer{};
        uint8_t soundTimer{};
        uint16_t opcode;

        std::default_random_engine randGen;
        std::uniform_int_distribution<unsigned long> randByte;

        typedef void (Chip8::*Chip8Func)();
	    Chip8Func table[0xF + 1];
	    Chip8Func table0[0xE + 1];
	    Chip8Func table8[0xE + 1];
	    Chip8Func tableE[0xE + 1];
	    Chip8Func tableF[0x65 + 1];

};