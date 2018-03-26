#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glm/glm.hpp>

#include <gamenge/common/common.hpp>
#include <gamenge/renderer/renderable.hpp>

TEST(RenderableTest, construct)
{
    GID shader = 214;
    GID mesh = 780;
    GID texture = 8635;

    Renderable renderable(shader, mesh, texture);

    EXPECT_EQ(shader, renderable.getShader());
    EXPECT_EQ(mesh, renderable.getMesh());
    EXPECT_EQ(texture, renderable.getTexture());
}

TEST(RenderableTest, setGetTranslation)
{
    Renderable renderable(817, 235, 690);

    glm::vec3 translation(872.142f, 543.817f, 832471.123f);
    renderable.setTranslation(glm::vec3(translation));
    EXPECT_EQ(translation, renderable.getTranslation());

    float newX = 9182.123f, newY = 8323.123f, newZ = 6712.4652f;

    renderable.setX(newX);
    EXPECT_EQ(newX, renderable.getTranslation().x);
    renderable.setY(newY);
    EXPECT_EQ(newY, renderable.getTranslation().y);
    renderable.setZ(newZ);
    EXPECT_EQ(newZ, renderable.getTranslation().z);
}

TEST(RenderableTest, setGetRotation)
{
    Renderable renderable(876, 124, 523);

    glm::vec3 rotation(117.123f, 5321.123f, 25410.163f);
    renderable.setRotation(rotation);
    EXPECT_EQ(rotation, renderable.getRotation());

    float newXRot = 172.541f, newYRot = 8124.12f, newZRot = 6051.1239f;
    
    renderable.setXRotation(newXRot);
    EXPECT_EQ(newXRot, renderable.getRotation().x);

    renderable.setYRotation(newYRot);
    EXPECT_EQ(newYRot, renderable.getRotation().y);

    renderable.setZRotation(newZRot);
    EXPECT_EQ(newZRot, renderable.getRotation().z);
}

TEST(RenderableTest, setGetScale)
{
    Renderable renderable(812, 515, 782);

    glm::vec3 scale(71982.12f, 23.02f, 123456.9876f);
    renderable.setScale(scale);
    EXPECT_EQ(scale, renderable.getScale());

    float newXScale = 987123.123f, newYScale = 734.123f, newZScale = 6271.421f;

    renderable.setXScale(newXScale);
    EXPECT_EQ(newXScale, renderable.getScale().x);

    renderable.setYScale(newYScale);
    EXPECT_EQ(newYScale, renderable.getScale().y);

    renderable.setZScale(newZScale);
    EXPECT_EQ(newZScale, renderable.getScale().z);
}