#include <gtest/gtest.h>
#include "../include/Chip8.hpp"

Chip8 Chip8Intilizer() {

}

TEST(OPCodeTest, TestOPNULL) {
    Chip8 c;
    EXPECT_NO_THROW(c.OP_NULL());
}

TEST(OPCodeTest, TestOP_00E0) {
    Chip8 c;
    //std::array<uint8_t, MEMORY_SIZE> buffer;
    //buffer.fill(1);
    c.video.fill(1);
    c.OP_00E0();

    // Verify that all values are now 0 after calling OP_00E0
    for (std::size_t i = 0; i < VIDEO_WIDTH * VIDEO_HEIGHT; ++i) {
        EXPECT_EQ(c.video[i], 0) << "Pixel at index " << i << " was not cleared. Has Value of " << c.video[i];
    }
}

TEST(OPCodeTest, TestOP_00EE) {

}