#include <chrono>
#include <random>
#include <cstdint>
#include <iostream>
#include <sstream>
#include "../include/Chip8.hpp"
#include "../include/Platform.hpp"

void displayRender(const std::array<uint32_t, 64 * 32>& video) {
	constexpr int WIDTH = 64;
	constexpr int HEIGHT = 32;

	std::ostringstream output;

	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		output << (video[i] != 0 ? "*" : " ");

		// Add a newline after each row
		if (i % WIDTH == WIDTH - 1) {
			output << "\n";
		}
	}

	// Flush the buffered output to the console
	std::cout << "\n\n\n\n" << output.str();
}

int main(int argc, char** argv) {
	//Chip8 chip;

	//chip.LoadROM("D:\\Code\\C++ projects\\Chip8-Emulator\\roms\\IBMLogo.ch8");
	//while (true) {
	//	chip.Cycles();
	//	displayRender(chip.video);
	//}
	/*if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
		std::exit(EXIT_FAILURE);
	}

	int videoScale = std::stoi(argv[1]);
	int cycleDelay = std::stoi(argv[2]);
	char const* romFilename = argv[3];

	Platform platform("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

	Chip8 chip8;
	chip8.LoadROM(romFilename);

	int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

	auto lastCycleTime = std::chrono::high_resolution_clock::now();
	bool quit = false;

	while (!quit)
	{
		quit = platform.ProcessInput(chip8.keypad);

		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

		if (dt > cycleDelay)
		{
			lastCycleTime = currentTime;

			chip8.Cycles();

			platform.Update(chip8.video, videoPitch);
		}
	}*/
	//SDL_Log("SDL initialized successfully!");


    // Main render loop
	Chip8 chip;
	Platform plat("title", 1920, 1080, &chip);
	plat.mainLoop();
	return 0;
}

