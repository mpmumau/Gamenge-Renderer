/* Library headers */
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/glu.h>

/* Application headers */
#include <gamenge/common/common.hpp>

/* Self header */
#include <gamenge/renderer/shader_data.hpp>

using namespace Gamenge;

ShaderData::ShaderData(Path vertFile, Path fragFile)
{
    loadProgram(vertFile, fragFile);
}

ShaderData::~ShaderData()
{
    destroy();
}

GLuint ShaderData::getProgram()
{
    return programID;
}

void ShaderData::destroy()
{
    glDeleteProgram(programID);
}

void ShaderData::loadProgram(Path vertFile, Path fragFile)
{
    programID = glCreateProgram();

    GLuint vertexShader = compileShader(vertFile, GL_VERTEX_SHADER);
    glAttachShader(programID, vertexShader);
    // Todo: Check for errors?

    GLuint fragmentShader = compileShader(fragFile, GL_FRAGMENT_SHADER);
    glAttachShader(programID, fragmentShader);
    // Todo: Check for errors?

    glLinkProgram(programID);

    GLboolean success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        // Todo: Throw an exception. GL shader program could not be linked.
        exit(1);
    }
}

GLuint ShaderData::compileShader(Path file, GLenum type)
{
    std::string src, tmp;
    std::ifstream fs;
    
    fs.open(file);
    
    if (!fs) {
        // Todo: Throw exception. File load error.
        exit(1);
    }

    while (getline(fs, tmp)) { 
        src += tmp + "\n";
    }
    
    fs.close();

    const GLchar *source[src.size()] = {
        src.c_str()
    };

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, source, NULL);
    glCompileShader(shader);

    GLboolean success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        // Todo: Throw exception. OpenGL could not create shader with source.
        exit(1);
    }

    return shader;
}