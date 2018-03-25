#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>

#include <gamenge/renderer/shader_data.hpp>

TEST(ShaderData, constructWithoutLinkingExceptions)
{
    EXPECT_THROW(ShaderData("", "", false), std::invalid_argument);
    EXPECT_THROW(ShaderData("abc123xyz", "", false), std::runtime_error);
    EXPECT_THROW(ShaderData("abc123xyz", "xyz123abc", false), std::runtime_error);
}