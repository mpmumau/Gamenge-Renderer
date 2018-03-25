#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>

#include <gamenge/renderer/texture_data.hpp>

TEST(TextureData, constructWithoutBindingExceptions)
{
    EXPECT_THROW(TextureData("", false), std::invalid_argument);
    EXPECT_THROW(TextureData("abc123xyz", false), std::runtime_error);
}