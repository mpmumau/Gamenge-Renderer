#ifndef GAMENGE_RENDERER_RENDERABLE_H
#define GAMENGE_RENDERER_RENDERABLE_H

/* Library headers */
#include <GL/glew.h>
#include <GL/glu.h>

#include <glm/glm.hpp>

/* Application headers */
#include <gamenge/common/common.h>

using namespace Gamenge;

namespace Gamenge {

    class Renderable {
    public:
        Renderable();
        Renderable(GID, GID, GID);

        void setTranslation(glm::vec3);
        void setX(GLfloat);
        void setY(GLfloat);
        void setZ(GLfloat);

        void setRotation(glm::vec3);
        void setXRotation(GLfloat);
        void setYRotation(GLfloat);
        void setZRotation(GLfloat);

        void setScale(glm::vec3);
        void setXScale(GLfloat);
        void setYScale(GLfloat);
        void setZScale(GLfloat);

        glm::vec3 getTranslation();
        glm::vec3 getRotation();
        glm::vec3 getScale();

        unsigned int getShaderDataID();
        unsigned int getMeshDataID();
        unsigned int getTextureDataID();
    private:
        glm::vec3 translation, rotation, scale;
        GID shaderDataID, meshDataID, textureDataID;

        void setDefaults();
    };

} // end namespace Gamenge

#endif