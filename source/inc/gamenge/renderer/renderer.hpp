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
     * @brief  Primary control class for the Gamenge::Renderer system.
     */
    class Renderer
    {
    public:
        /**
         * @brief  Default constructor.
         */
        Renderer();

        /**
         * @brief  Initialize the renderer object.
         */
        void init();

        /**
         * @brief  Render all objects within the system.
         */
        void render();

        /**
         * @brief  Adds a new renderable.
         *
         * @param[in]  shaderID  The GID of the shader program with which to render.
         * @param[in]  meshID  The GID of a mesh object to render. }
         * @param[in]  textureID  The GID of a texture object with which to render.
         *
         * @return  A GID representing the newly created renderable object.
         */
        GID addRenderable(GID, GID, GID);

        /**
         * @brief  Adds a shader and immediately link it.
         *
         * @param[in]  vertFile  The OpenGL vertex shader source.
         * @param[in]  fragFile  The OpenGL fragment shader source.
         *
         * @throw  std::invalid_argument  If the paths given are null or empty.
         * @throw  std::runtime_error  If there was an error loading the files, or with OpenGL calls.
         *
         * @return  A GID representing the newly created shader object.
         */
        GID addShader(Path, Path);

        /**
         * @brief      Adds a new shader.
         *
         * @param[in]  vertFile  The OpenGL vertex shader source.
         * @param[in]  fragFile  The OpenGL fragment shader source.
         * @param[in]  shouldLink  Whether or not to automatically link the shader program. 
         *
         * @throw  std::invalid_argument  If the paths given are null or empty.
         * @throw  std::runtime_error  If there was an error loading the files, or with OpenGL calls.
         *
         * @return     A GID representing the newly created shader data object.
         */
        GID addShader(Path, Path, bool);

        /**
         * @brief      Adds a new mesh.
         *
         * @param[in]  meshFile  The mesh file from which to retrieve mesh data.
         *
         * @throw  std::invalid_argument  If the given path is null or empty.
         * @throw  std::runtime_error  If there was an error loading the file, or with OpenGL calls.
         *
         * @return     A GID representing the newly created mesh data object.
         */
        GID addMesh(Path);

        /**
         * @brief      Adds a new mesh.
         *
         * @param[in]  meshFile  The mesh file from which to retrieve mesh data.
         * @param[in]  shouldBind  Whether or not the OpenGL buffers should be bound immediately.
         *
         * @throw  std::invalid_argument  If the given path is null or empty.
         * @throw  std::runtime_error  If there was an error loading the file, or with OpenGL calls.
         *
         * @return     A GID representing the newly created mesh data object.
         */
        GID addMesh(Path, bool);

        /**
         * @brief  Adds a new texture.
         *
         * @param[in]  textureFile  The BMP texture file to load.
         *
         * @throw  std::invalid_argument  If the given path is null or empty.
         * @throw  std::runtime_error  If there was an error loading the file, or with OpenGL calls.
         *     
         * @return  A GID representing the newly created mesh data object.
         */
        GID addTexture(Path);

        /**
         * @brief  Adds a new texture.
         *
         * @param[in]  textureFile  The BMP texture file to load.
         * @param[in]  shouldBind  Whether or not the OpenGL buffers should be bound immediately.
         *
         * @throw  std::invalid_argument  If the given path is null or empty.
         * @throw  std::runtime_error  If there was an error loading the file, or with OpenGL calls.
         *     
         * @return  A GID representing the newly created mesh data object.
         */
        GID addTexture(Path, bool);

        
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