/* Library headers */
#include <GL/glew.h>
#include <GL/glu.h>

#include <glm/glm.hpp>

/* Application headers */
#include <gamenge/common/common.h>

/* Self header */
#include <gamenge/renderer/renderable.h>

using namespace Gamenge;

Renderable::Renderable()
{
    setDefaults();
}

Renderable::Renderable(GID shaderDataID, GID meshDataID, GID textureDataID)
{
    setDefaults();

    this->shaderDataID = shaderDataID;
    this->meshDataID = meshDataID;
    this->textureDataID = textureDataID;
}

void Renderable::setTranslation(glm::vec3 translation)
{
    this->translation = translation;
}

void Renderable::setX(GLfloat x)
{
    translation.x = x;
}

void Renderable::setY(GLfloat y)
{
    translation.y = y; 
}

void Renderable::setZ(GLfloat z)
{
    translation.z = z;
}

void Renderable::setRotation(glm::vec3 rotation)
{
    this->rotation = rotation;
}

void Renderable::setXRotation(GLfloat rotation)
{
    rotation.x = rotation;
}

void Renderable::setYRotation(GLfloat rotation)
{
    rotation.y = rotation;
}

void Renderable::setZRotation(GLfloat rotation)
{
    rotation.z = rotation;
}

void Renderable::setScale(glm::vec3 scale)
{
    this->scale = scale;
}

void Renderable::setXScale(GLfloat scale)
{
    scale.x = scale;
}

void Renderable::setYScale(GLfloat scale)
{
    scale.y = scale;
}

void Renderable::setZScale(GLfloat scale)
{
    scale.z = scale;
}

glm::vec3 Renderable::getTranslation()
{
    return translation;
}

glm::vec3 Renderable::getRotation()
{
    return rotation;
}

glm::vec3 Renderable::getScale()
{
    return scale;
}

unsigned int Renderable::getShaderDataID()
{
    return shaderDataID;
}

unsigned int Renderable::getMeshDataID()
{
    return meshDataID;
}

unsigned int *Renderable::getTextureData()
{
    return textureDataID;
}

void Renderable::setDefaults()
{
    translation = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f);

    shaderData = 0;
    meshData = 0;
    textureData = 0;
}