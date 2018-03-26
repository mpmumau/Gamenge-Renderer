#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>

#include <gamenge/renderer/renderer.hpp>

TEST(RendererTest, constructor)
{
    Renderer renderer;

    Renderable *renderable = renderer.getRenderable(23);
    EXPECT_EQ(NULL, renderable);

    Camera *camera = renderer.getCamera(123);
    EXPECT_EQ(NULL, camera);

    EXPECT_EQ(0, renderer.getActiveCamera());
}

TEST(RendererTest, addRenderable)
{
    Renderer renderer;

    GID shader = renderer.addShader("data/test_vertex_shader.vert", "data/test_fragment_shader.frag", false);
    GID mesh = renderer.addMesh("data/test_mesh.obj", false);
    GID texture = renderer.addTexture("data/test_bitmap_good.bmp", false);

    GID renderable = renderer.addRenderable(shader, mesh, texture);

    EXPECT_TRUE(0 != renderable);
    EXPECT_TRUE(NULL != renderer.getRenderable(renderable));
}

TEST(RendererTest, addShader)
{
    Renderer renderer;

    GID shader = renderer.addShader("data/test_vertex_shader.vert", "data/test_fragment_shader.frag", false);

    EXPECT_TRUE(0 != shader);
}

TEST(RendererTest, addShaderExceptions)
{
    Renderer renderer;

    EXPECT_THROW(renderer.addShader(NULL, NULL, false), std::invalid_argument);
    EXPECT_THROW(renderer.addShader("", "", false), std::invalid_argument);
    EXPECT_THROW(renderer.addShader("abc123xyz", "", false), std::runtime_error);
    EXPECT_THROW(renderer.addShader("", "xyz123abc", false), std::invalid_argument);
    EXPECT_THROW(renderer.addShader("xyz123abc", "abc123xyz", false), std::runtime_error);
}

TEST(RendererTest, addMesh)
{
    Renderer renderer;

    GID mesh = renderer.addMesh("data/test_mesh.obj", false);

    EXPECT_TRUE(0 != mesh);
}

TEST(RendererTest, addMeshExceptions)
{
    Renderer renderer;

    EXPECT_THROW(renderer.addMesh("", false), std::invalid_argument);
    EXPECT_THROW(renderer.addMesh("xyz123abc", false), std::runtime_error);
}

TEST(RendererTest, addTexture)
{
    Renderer renderer;

    GID texture = renderer.addTexture("data/test_bitmap_good.bmp", false);

    EXPECT_TRUE(0 != texture);
}

TEST(RendererTest, addTextureExceptions)
{
    Renderer renderer;

    EXPECT_THROW(renderer.addTexture("", false), std::invalid_argument);
    EXPECT_THROW(renderer.addTexture("xyz123abc", false), std::runtime_error);
}

TEST(RendererTest, addCamera)
{
    Renderer renderer;

    GID cameraID = renderer.addCamera();
    EXPECT_TRUE(cameraID != 0);

    Camera *camera = renderer.getCamera(cameraID);
    EXPECT_TRUE(camera != NULL);
}

TEST(RendererTest, getRenderable)
{
    Renderer renderer;

    Renderable *renderable;

    renderable = renderer.getRenderable(123);
    EXPECT_TRUE(renderable == NULL);
}

TEST(RendererTest, getCamera)
{
    Renderer renderer;

    Camera *camera;

    camera = renderer.getCamera(123);
    EXPECT_TRUE(camera == NULL);
}

TEST(RendererTest, setActiveCamera)
{
    Renderer renderer;

    GID camera = renderer.addCamera();
    renderer.setActiveCamera(camera);

    EXPECT_EQ(camera, renderer.getActiveCamera());
}