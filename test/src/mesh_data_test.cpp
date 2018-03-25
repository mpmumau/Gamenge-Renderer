#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>

#include <gamenge/renderer/mesh_data.hpp>

TEST(MeshData, constructWithoutBindingExceptions)
{
    EXPECT_THROW(MeshData("", false), std::invalid_argument);
    EXPECT_THROW(MeshData("abc123xyz", false), std::runtime_error);
}