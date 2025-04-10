#include "math_utils.h"
#include <iostream>
#include <gtest/gtest.h>
TEST(SumaTest, Positivos) {
    EXPECT_EQ(sumar(2, 3), 5);
}

TEST(SumaTest, Negativos) {
    EXPECT_EQ(sumar(-1, -4), -5);
}

TEST(SumaTest, Mixtos) {
    EXPECT_EQ(sumar(-1, 4), 3);
}

int main(int argc, char **argv) {
    std::cout << "Ayuda 1" << std::endl;
    int x = 4;
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "Ayuda 2" << std::endl;
    return RUN_ALL_TESTS();
}