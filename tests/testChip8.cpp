#include <gtest/gtest.h>
#include "../include/Chip8.hpp"


TEST(OPCodeTest, TestOPNULL) {
    Chip8 c;
    EXPECT_NO_THROW(c.OP_NULL());
}