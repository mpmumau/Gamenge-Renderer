#ifndef GAMENGE_RENDERER_SHADER_DATA_H
#define GAMENGE_RENDERER_SHADER_DATA_H

/* Library headers */
#include <GL/glew.h>
#include <GL/glu.h>

/* Application headers */
#include <gamenge/common/common.h>

using namespace Gamenge;

namespace Gamenge {

    class ShaderData
    {
    public:
        ShaderData(Path, Path);
        ~ShaderData();

        GLuint getProgram();
        void destroy();
    private:
        GLuint programID;

        void loadProgram(Path, Path);
        GLuint compileShader(Path, GLenum);
    };

} // end namespace Gamenge

#endif