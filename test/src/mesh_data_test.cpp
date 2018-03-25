#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>

#include <gamenge/renderer/mesh_data.hpp>

TEST(MeshData, construct)
{
    EXPECT_NO_THROW(MeshData("data/test_mesh.obj", false));
}

TEST(MeshData, constructWithoutBindingExceptions)
{
    EXPECT_THROW(MeshData("", false), std::invalid_argument);
    EXPECT_THROW(MeshData("abc123xyz", false), std::runtime_error);
}

TEST(MeshData, correctData)
{
    MeshData meshData("data/test_mesh.obj", false);

    EXPECT_EQ(360, meshData.getNumVertices());
    EXPECT_EQ(360, meshData.getNumNormals());
    EXPECT_EQ(240, meshData.getNumUVs());
    EXPECT_EQ(90, meshData.getNumIndices());
}