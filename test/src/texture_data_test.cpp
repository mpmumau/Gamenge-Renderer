#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>

// #include <stdio.h>
// #include <fstream>
// #include <string.h>
// #include <string>

#include <gamenge/renderer/texture_data.hpp>

TEST(TextureData, construct)
{
    EXPECT_NO_THROW(TextureData("data/test_bitmap_good.bmp", false));
}

TEST(TextureData, constructExceptions)
{
    EXPECT_THROW(TextureData("", false), std::invalid_argument);
    EXPECT_THROW(TextureData("abc123xyz", false), std::runtime_error);
    EXPECT_THROW(TextureData("data/test_bitmap_empty.bmp", false), std::runtime_error);
    EXPECT_THROW(TextureData("data/test_bitmap_wrong_depth.bmp", false), std::runtime_error);
}

TEST(TextureData, numPixelsCorrect)
{
    TextureData textureData("data/test_bitmap_good.bmp", false);
    EXPECT_EQ(64 * 64 * 3, textureData.getNumPixels());
}
