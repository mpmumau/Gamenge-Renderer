/* Library headers */
#include <stdexcept>
#include <fstream>
#include <string.h>
#include <GL/glew.h>
#include <string>
#include <stdio.h>

/* Application headers */
#include <gamenge/common/common.hpp>

/* Self header */
#include <gamenge/renderer/shader_data.hpp>

using namespace Gamenge;

ShaderData::ShaderData(Path vertFile, Path fragFile)
{
    init();

    try {
        load(vertFile, fragFile);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }
}

ShaderData::ShaderData(Path vertFile, Path fragFile, bool shouldLink)
{
    init();

    try {
        load(vertFile, fragFile, shouldLink);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }
}

ShaderData::~ShaderData()
{
    destroy();
}

void ShaderData::link()
{
    if (hasLinked) {
        return;
    }

    GLint success;

    const GLchar *vSource = (const GLchar *) vertexSource.c_str();
    const GLchar *fSource =  (const GLchar *) fragSource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        glDeleteShader(vertexShader);
        throw std::runtime_error("OpenGL could not compile the vertex shader.");
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        glDeleteShader(fragmentShader);
        throw std::runtime_error("OpenGL could not compile the fragment shader.");
    }

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    // Todo: Delete and detach shaders? Look it up...

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        throw std::runtime_error("OpenGL could not link the shader program.");
    }

    hasLinked = true;
}

GLuint ShaderData::getProgram()
{
    return programID;
}

std::string ShaderData::getVertexSource()
{
    return vertexSource;
}

std::string ShaderData::getFragmentSource()
{
    return fragSource;
}

void ShaderData::destroy()
{
    if (programID != 0) {
        glDeleteProgram(programID);
    }
}

void ShaderData::init()
{
    programID = 0;
    vertexSource.clear();
    fragSource.clear();
    hasLinked = false;
}

void ShaderData::load(Path vertFile, Path fragFile)
{
    try {
        load(vertFile, fragFile, true);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }
}

void ShaderData::load(Path vertFile, Path fragFile, bool shouldLink)
{
    try {
        vertexSource = parseSource(vertFile);
        fragSource = parseSource(fragFile);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }

    if (shouldLink) {
        try {
            link();
        } catch(const std::runtime_error& e) {
            throw e;
        }
    }
}

std::string ShaderData::parseSource(Path file)
{
    if (file == NULL) {
        throw std::invalid_argument("Supplied file path was null.");
    }

    if (strlen(file) == 0) {
        throw std::invalid_argument("Supplied file path was an empty string.");
    }

    std::ifstream fs(file);
    if (!fs) {
        throw std::runtime_error("Shader file could not be opened.");
    }

    std::string src((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    fs.close();

    return src;
}