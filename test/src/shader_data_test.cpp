#include <stdexcept>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gamenge/renderer/shader_data.hpp>

TEST(ShaderData, construct)
{
    EXPECT_NO_THROW(ShaderData("data/test_vertex_shader.vert", "data/test_fragment_shader.frag", false));
}

TEST(ShaderData, constructExceptions)
{
    EXPECT_THROW(ShaderData("", "", false), std::invalid_argument);
    EXPECT_THROW(ShaderData("abc123xyz", "", false), std::runtime_error);
    EXPECT_THROW(ShaderData("abc123xyz", "xyz123abc", false), std::runtime_error);
}

TEST(ShaderData, correctData)
{
    ShaderData shaderData("data/test_vertex_shader.vert", "data/test_fragment_shader.frag", false);

    std::string vertSource(shaderData.getVertexSource());
    std::string fragSource(shaderData.getFragmentSource());

    EXPECT_TRUE(vertSource.find("#version") != std::string::npos);
    EXPECT_TRUE(fragSource.find("#version") != std::string::npos);

    EXPECT_EQ(0, vertSource.find("#version"));
    EXPECT_EQ(0, fragSource.find("#version"));
}