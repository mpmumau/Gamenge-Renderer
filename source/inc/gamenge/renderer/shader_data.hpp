#ifndef GAMENGE_RENDERER_SHADER_DATA_H
#define GAMENGE_RENDERER_SHADER_DATA_H

/* Library headers */
#include <string>
#include <GL/glew.h>

/* Application headers */
#include <gamenge/common/common.hpp>

using namespace Gamenge;

namespace Gamenge {
    /**
     * @brief  A data object representing an OpenGL shader program.
     */
    class ShaderData
    {
    public:
        /**
         * @brief  Construct a shader, and immediately load into OpenGL.
         *
         * @param[in]  vertFile  A vertex shader source code file path.
         * @param[in]  fragFile  A fragment shader source code file path.
         * 
         * @throw  std::invalid_argument  If the paths given are null or empty.
         * @throw  std::runtime_error  If there was an error loading the files, or with OpenGL calls.
         */
        ShaderData(Path, Path);

        /**
         * @brief  Construct a shader, and, optionally, immediately load into OpenGL
         *
         * @param[in]  vertFile  A vertex shader source code file path.
         * @param[in]  fragFile  A fragment shader source code file path.
         * @param[in]  shouldLink  Whether or not to immediately load and link the program in OpenGL.
         * 
         * @throw  std::invalid_argument  If the paths given are null or empty.
         * @throw  std::runtime_error  If there was an error loading the files, or with OpenGL calls.
         */
        ShaderData(Path, Path, bool);

        /**
         * @brief  Load and link the program in OpenGL, if it has not already done so.
         */
        void link();

        /**
         * @brief  Get the OpenGL program ID for the shader.
         *
         * @return  The OpenGL program ID.
         */
        GLuint getProgram();

        /**
         * @brief  Gets the vertex shader source.
         *
         * @return  The vertex shader source.
         */
        std::string getVertexSource();

        /**
         * @brief      Gets the fragment shader source.
         *
         * @return     The fragment shader source.
         */
        std::string getFragmentSource();

        /**
         * @brief  Destroy the shader's OpenGL program.
         */
        void destroy();
    private:
        GLuint programID;
        std::string vertexSource;
        std::string fragSource;
        bool hasLinked;

        void init();
        void load(Path, Path);
        void load(Path, Path, bool);
        std::string parseSource(Path);
    };

} // end namespace Gamenge

#endif