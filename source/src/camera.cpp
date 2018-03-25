/* Library headers */
#include <GL/glew.h>
#include <glm/glm.hpp>

/* Application headers */
#include <gamenge/common/common.hpp>

/* Self header */
#include <gamenge/renderer/camera.hpp>

using namespace Gamenge;

Camera::Camera()
{
    setDefaults();
}

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 upDir)
{
    setDefaults();

    this->position = position;
    this->target = target;
    this->upDir = upDir;
}

void Camera::setDefaults()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    target = glm::vec3(0.0f, 0.0f, -1.0f);
    upDir = glm::vec3(0.0f, 1.0f, 0.0f);

    // Todo: abstract this up a bit; put some of these values into the Renderer class.
    fov = glm::radians(45.0f);
    aspectRatio = 16.0f / 9.0f;
    clipNear = 0.01f;
    clipFar = 110.0f;
}

glm::vec3 Camera::getPosition()
{
    return position;
}

glm::vec3 Camera::getTarget()
{
    return target;
}

glm::vec3 Camera::getUpDir()
{
    return upDir;
}

GLfloat Camera::getFOV()
{
    return fov;
}

GLfloat Camera::getAspectRatio()
{
    return aspectRatio;
}

GLfloat Camera::getClipNear()
{
    return clipNear;
}

GLfloat Camera::getClipFar()
{
    return clipFar;
}

void Camera::setPosition(glm::vec3 position)
{
    this->position = position;
}

void Camera::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    position = glm::vec3(x, y, z);
}

void Camera::setTarget(glm::vec3 target)
{
    this->target = target;
}

void Camera::setUpDir(glm::vec3 upDir)
{
    this->upDir = upDir;
}

void Camera::setFOV(GLfloat fov)
{
    this->fov = fov;
}

void Camera::setAspectRatio(GLfloat aspectRatio)
{
    this->aspectRatio = aspectRatio;
}

void Camera::setClipNear(GLfloat clipNear)
{
    this->clipNear = clipNear;
}

void Camera::setClipFar(GLfloat clipFar)
{
    this->clipFar = clipFar;
}
