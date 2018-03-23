#ifndef GAMENGE_RENDERER_CAMERA_H
#define GAMENGE_RENDERER_CAMERA_H

/* Library headers */
#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

/* Application headers */
#include <gamenge/common/common.h>

using namespace Gamenge;

namespace Gamenge {

    class Camera {
    public:
        Camera();
        Camera(glm::vec3, glm::vec3, glm::vec3);

        glm::vec3 getPosition();
        glm::vec3 getTarget();
        glm::vec3 getUpDir();
        GLfloat getFOV();
        GLfloat getAspectRatio();
        GLfloat getClipNear();
        GLfloat getClipFar();

        void setPosition(glm::vec3);
        void setPosition(GLfloat, GLfloat, GLfloat);
        void setTarget(glm::vec3);
        void setUpDir(glm::vec3);
        void setFOV(GLfloat);
        void setAspectRatio(GLfloat);
        void setClipNear(GLfloat);
        void setClipFar(GLfloat);
    private:
        glm::vec3 position, target, upDir;
        GLfloat fov, aspectRatio, clipNear, clipFar;

        void setDefaults();
    };

} // end namespace Gamenge

#endif