#ifndef GAMENGE_RENDERER_RENDERER_H
#define GAMENGE_RENDERER_RENDERER_H

/* Library headers */
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>

/* Application headers */
#include <gamenge/common/common.hpp>
#include <gamenge/renderer/camera.hpp>
#include <gamenge/renderer/mesh_data.hpp>
#include <gamenge/renderer/renderable.hpp>
#include <gamenge/renderer/shader_data.hpp>
#include <gamenge/renderer/texture_data.hpp>

using namespace Gamenge;

namespace Gamenge {
    /**
     * @brief Primary control class for the Gamenge::Renderer system.
     */
    class Renderer
    {
    public:
        /**
         * @brief Initialize the renderer object.
         */
        void init();

        /**
         * @brief Render all objects within the system.
         */
        void render();

        /**
         * @brief      Adds a renderable.
         *
         * @param[in]  shaderID  The GID of the shader program with which to render.
         * @param[in]  meshID  The GID of a mesh object to render. }
         * @param[in]  textureID  The GID of a texture object with which to render.
         *
         * @return     A GID representing the newly created renderable object.
         */
        GID addRenderable(GID, GID, GID);
        GID addShader(Path, Path);
        GID addMesh(Path);
        GID addTexture(Path);
        GID addCamera();

        Renderable *getRenderable(GID);
        Camera *getCamera(GID);

        void setActiveCamera(GID);
        GID getActiveCamera();

        void destroy();

    private:
        std::map<GID, Renderable> renderables;
        std::map<GID, ShaderData> shaders;
        std::map<GID, MeshData> meshes;
        std::map<GID, TextureData> textures;
        std::map<GID, Camera> cameras;

        GID activeCamera;
        GID nextRenderable, nextShader, nextMesh, nextTexture, nextCamera;

        void setNextRenderable();
        void setNextShader();
        void setNextMesh();
        void setNextTexture();
        void setNextCamera();

        glm::mat4 getProjectionMatrix();
        glm::mat4 getViewMatrix();
        glm::mat4 getModelMatrix(Renderable *);
        glm::mat4 getMVPMatrix(glm::mat4, glm::mat4, glm::mat4);
    };

} // end namespace Gamenge

#endif