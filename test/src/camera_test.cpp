#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>

#include <glm/glm.hpp>

#include <gamenge/renderer/camera.hpp>

TEST(Camera, constructor)
{
    Camera camera;

    EXPECT_EQ(glm::vec3(0.0f, 0.0f, 0.0f), camera.getPosition());
    EXPECT_EQ(glm::vec3(0.0f, 0.0f, -1.0f), camera.getTarget());
    EXPECT_EQ(glm::vec3(0.0f, 1.0f, 0.0f), camera.getUpDir());
}

TEST(Camera, constructorWithThreeVectors)
{
    glm::vec3 position, target, upDir;

    position = glm::vec3(123.123f, 456.456f, 789.789f);
    target = glm::vec3(789.789f, 654.654f, 123.123f);
    upDir = glm::vec3(654.654f, 789.789f, 321.321f);

    Camera camera = Camera(position, target, upDir);

    EXPECT_EQ(position, camera.getPosition());
    EXPECT_EQ(target, camera.getTarget());
    EXPECT_EQ(upDir, camera.getUpDir());
}

TEST(Camera, setGetPosition)
{
    Camera camera;

    glm::vec3 position = glm::vec3(543.210f, 987.654f, 321.098f);
    camera.setPosition(position);

    EXPECT_EQ(position, camera.getPosition());

    camera.setPosition(321.098f, 987.654f, 543.210f);
    EXPECT_EQ(glm::vec3(321.098f, 987.654f, 543.210f), camera.getPosition());
}

TEST(Camera, setGetTarget)
{
    Camera camera;

    glm::vec3 target = glm::vec3(441.145f, 183.342f, 523.0123f);

    camera.setTarget(target);
    EXPECT_EQ(target, camera.getTarget());
}

TEST(Camera, setGetUpDir)
{
    Camera camera;

    glm::vec3 upDir = glm::vec3(918.314f, 248.542f, 837.519f);

    camera.setTarget(upDir);
    EXPECT_EQ(upDir, camera.getTarget());
}