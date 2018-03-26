#ifndef GAMENGE_RENDERER_CAMERA_H
#define GAMENGE_RENDERER_CAMERA_H

/* Library headers */
#include <GL/glew.h>
#include <glm/glm.hpp>

/* Application headers */
#include <gamenge/common/common.hpp>

using namespace Gamenge;

namespace Gamenge {

    class Camera {
    public:
        /**
         * @brief  Construct a camera object.
         */
        Camera();

        /**
         * @brief  Construct a camera object, using vector parameters for initialization.
         *
         * @param[in]  position  The initial position of the camera.
         * @param[in]  target  The view target of the camera.
         * @param[in]  upDir  The direction of "up" to the camera.
         */
        Camera(glm::vec3, glm::vec3, glm::vec3);

        /**
         * @brief  Get the position of the camera.
         *
         * @return  The position of the camera.
         */
        glm::vec3 getPosition();

        /**
         * @brief  Get the view target of the camera.
         *
         * @return  The view target of the camera.
         */
        glm::vec3 getTarget();

        /**
         * @brief  Get the "up" direction of the camera.
         *
         * @return  The "up" direction of the camera.
         */
        glm::vec3 getUpDir();

        /**
         * @brief  Gets the field of view of the camera.
         *
         * @return  The field of view of the camera.
         */
        GLfloat getFOV();

        /**
         * @brief  Get the aspect ratio of the camera.
         *
         * @return  The aspect ratio of the camera.
         */
        GLfloat getAspectRatio();

        /**
         * @brief  Gets the near clipping value of the camera.
         *
         * @return  The near clipping value of the camera.
         */
        GLfloat getClipNear();

        /**
         * @brief  Gets the far clipping value of the camera.
         *
         * @return  The far clipping value of the camera.
         */
        GLfloat getClipFar();

        /**
         * @brief  Set the position of the camera.
         *
         * @param[in]  position  The position to set for the camera.
         */
        void setPosition(glm::vec3);

        /**
         * @brief  Set the position of the camera, using floats.
         *
         * @param[in]  x  The x position to set for the camera.
         * @param[in]  y  The y position to set for the camera.
         * @param[in]  z  The z position to set for the camera.
         */
        void setPosition(GLfloat, GLfloat, GLfloat);

        /**
         * @brief  Set the view target of the camera.
         *
         * @param[in]  target  The view target to set for the camera.
         */
        void setTarget(glm::vec3);

        /**
         * @brief  Set the "up" direction of the camera.
         *
         * @param[in]  upDir  The "up" direction to set for the camera.
         */
        void setUpDir(glm::vec3);

        /**
         * @brief  Set the field of vision of the camera.
         *
         * @param[in]  fov  The field of vision value to set for the camera.
         */
        void setFOV(GLfloat);

        /**
         * @brief  Set the aspect ratio of the camera.
         *
         * @param[in]  aspectRatio  The aspect ratio to set for the camera.
         */
        void setAspectRatio(GLfloat);

        /**
         * @brief  Set the near clipping value for the camera.
         *
         * @param[in]  clipNear  The near clipping value to set for the camera.
         */
        void setClipNear(GLfloat);

        /**
         * @brief  Set the far clipping value for the camera.
         *
         * @param[in]  clipFar  The far clipping value for the camera.
         */
        void setClipFar(GLfloat);
    private:
        glm::vec3 position, target, upDir;
        GLfloat fov, aspectRatio, clipNear, clipFar;

        void setDefaults();
    };

} // end namespace Gamenge

#endif