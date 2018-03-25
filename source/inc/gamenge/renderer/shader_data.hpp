#ifndef GAMENGE_RENDERER_SHADER_DATA_H
#define GAMENGE_RENDERER_SHADER_DATA_H

/* Library headers */
#include <GL/glew.h>

/* Application headers */
#include <gamenge/common/common.hpp>

using namespace Gamenge;

namespace Gamenge {

    class ShaderData
    {
    public:
        ShaderData(Path, Path);
        ShaderData(Path, Path, bool);
        ~ShaderData();

        void link();
        GLuint getProgram();
        const GLchar *getVertexSource();
        const GLchar *getFragmentSource();
        void destroy();
    private:
        GLuint programID;
        const GLchar *vertexSource;
        const GLchar *fragSource;

        void init();
        void load(Path, Path);
        void load(Path, Path, bool);
        const GLchar *parseSource(Path);
    };

} // end namespace Gamenge

#endif