#ifndef GAMENGE_RENDERER_RENDERABLE_H
#define GAMENGE_RENDERER_RENDERABLE_H

/* Library headers */
#include <GL/glew.h>
#include <glm/glm.hpp>

/* Application headers */
#include <gamenge/common/common.hpp>

using namespace Gamenge;

namespace Gamenge {

    class Renderable {
    public:
        /**
         * @brief  Construct a new renderable.
         *
         * @param[in]  shaderDataID  The shader to use when rendering.
         * @param[in]  meshDataID  The mesh of the renderable.
         * @param[in]  textureDataID  The texture to use when rendering.
         */
        Renderable(GID, GID, GID);

        /**
         * @brief  Set the translation value.
         *
         * @param[in]  translation  The new translation value.
         */
        void setTranslation(glm::vec3);

        /**
         * @brief  Sets the x component of the translation value.
         *
         * @param[in]  x  The new x translation value.
         */
        void setX(GLfloat);

        /**
         * @brief  Sets the x component of the translation value.
         *
         * @param[in]  y  The new y translation value.
         */
        void setY(GLfloat);
        /**
         * @brief  Sets the z component of the translation value.
         *
         * @param[in]  z  The new z translation value.
         */
        void setZ(GLfloat);

        /**
         * @brief  Sets the rotation value.
         *
         * @param[in]  rotation  The new rotation value.
         */
        void setRotation(glm::vec3);

        /**
         * @brief  Sets the x component of the rotation value.
         *
         * @param[in]  x  The new x rotation value.
         */
        void setXRotation(GLfloat);

        /**
         * @brief  Sets the y component of the rotation value.
         *
         * @param[in]  y  The new y rotation value.
         */
        void setYRotation(GLfloat);

        /**
         * @brief  Sets the z component of the rotation value.
         *
         * @param[in]  z  The new z rotation value.
         */
        void setZRotation(GLfloat);

        /**
         * @brief  Sets the scale value.
         *
         * @param[in]  scale  The new scale value.
         */
        void setScale(glm::vec3);

        /**
         * @brief  Sets the x component of the scale value.
         *
         * @param[in]  x  The new x scale value.
         */
        void setXScale(GLfloat);

        /**
         * @brief  Sets the y component of the scale value.
         *
         * @param[in]  y  The new y scale value.
         */
        void setYScale(GLfloat);

        /**
         * @brief  Sets the z component of the scale value.
         *
         * @param[in]  z  The new z scale value.
         */
        void setZScale(GLfloat);

        /**
         * @brief  Gets the translation value.
         *
         * @return  The translation value.
         */
        glm::vec3 getTranslation();

        /**
         * @brief  Gets the rotation value.
         *
         * @return  The rotation value.
         */
        glm::vec3 getRotation();

        /**
         * @brief  Gets the scale value.
         *
         * @return  The scale value.
         */
        glm::vec3 getScale();

        /**
         * @brief  Get the GID of the shader.
         *
         * @return  The GID of the shader.
         */
        GID getShader();

        /**
         * @brief  Get the GID of the mesh.
         *
         * @return  The GID of the mesh.
         */
        GID getMesh();

        /**
         * @brief  Get the GID of the texture.
         *
         * @return  The GID of the texture.
         */
        GID getTexture();
    private:
        glm::vec3 translation, rotation, scale;
        GID shaderDataID, meshDataID, textureDataID;

        void setDefaults();
    };

} // end namespace Gamenge

#endif