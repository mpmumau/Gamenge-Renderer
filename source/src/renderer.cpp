/* Library headers */
#include <map>
#include <stdexcept>
#include <stdio.h>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

/* Application headers */
#include <gamenge/common/common.hpp>
#include <gamenge/renderer/camera.hpp>
#include <gamenge/renderer/mesh_data.hpp>
#include <gamenge/renderer/renderable.hpp>
#include <gamenge/renderer/shader_data.hpp>
#include <gamenge/renderer/texture_data.hpp>

/* Self header */
#include <gamenge/renderer/renderer.hpp>

using namespace Gamenge;

Renderer::Renderer()
{
    renderables.clear();
    shaders.clear();
    meshes.clear();
    textures.clear();
    cameras.clear();

    activeCamera = 0;

    nextRenderable = 1;
    nextShader = 1;
    nextMesh = 1;
    nextTexture = 1;
    nextCamera = 1;
}

void Renderer::init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}

void Renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (renderables.size() < 1) {
        return;
    }

    GLuint programID;

    ShaderData *shaderData;
    TextureData *textureData;
    MeshData *meshData;

    GLuint u_MVPMatrix, u_ModelMatrix, u_ViewMatrix, u_ProjectionMatrix, u_TextureSampler, u_LightPosition;
    glm::mat4 MVPMatrix, modelMatrix, viewMatrix, projectionMatrix;

    projectionMatrix = getProjectionMatrix();
    viewMatrix = getViewMatrix();

    Renderable *renderable;

    for (std::map<GID, Renderable>::iterator r = renderables.begin();
            r != renderables.end(); 
            ++r)
    {
        renderable = &(r->second);

        if (shaders.count(renderable->getShader()) == 0) {
            continue;
        }
        shaderData = &(shaders.at(renderable->getShader()));

        if (textures.count(renderable->getTexture()) == 0) {
            continue;
        }
        textureData = &(textures.at(renderable->getTexture()));

        if (meshes.count(renderable->getMesh()) == 0) {
            continue;
        }
        meshData = &(meshes.at(renderable->getMesh()));

        programID = shaderData->getProgram();
        glUseProgram(programID);

        /* Calculate and bind matrices */
        modelMatrix = getModelMatrix(renderable);
        MVPMatrix = getMVPMatrix(modelMatrix, viewMatrix, projectionMatrix);

        u_MVPMatrix = glGetUniformLocation(programID, "MVP");
        u_ModelMatrix = glGetUniformLocation(programID, "ModelMatrix");
        u_ViewMatrix = glGetUniformLocation(programID, "ViewMatrix");
        u_ProjectionMatrix = glGetUniformLocation(programID, "ProjectionMatrix");
        u_TextureSampler = glGetUniformLocation(programID, "TexSampler");
        u_LightPosition = glGetUniformLocation(programID, "LightPosition");

        glUniformMatrix4fv(u_ProjectionMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
        glUniformMatrix4fv(u_ViewMatrix, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(u_ModelMatrix, 1, GL_FALSE, &modelMatrix[0][0]);
        glUniformMatrix4fv(u_MVPMatrix, 1, GL_FALSE, &MVPMatrix[0][0]);
        glUniform3f(u_LightPosition, 0.0f, 0.0f, 0.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureData->getTextureBuffer());
        glUniform1i(u_TextureSampler, 0);

        // Vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, meshData->getVertexBuffer());
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        // UVS
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, meshData->getUVBuffer());
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        // Normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, meshData->getNormalBuffer());
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        glDrawArrays(GL_TRIANGLES, 0, meshData->getNumVertices());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }
}

GID Renderer::addRenderable(GID shader, GID mesh, GID texture)
{
    if (shaders.count(shader) == 0) {
        throw std::invalid_argument("Shader does not exist.");
    }

    if (meshes.count(mesh) == 0) {
        throw std::invalid_argument("Mesh does not exist.");
    }

    if (textures.count(texture) == 0) {
        throw std::invalid_argument("Texture does not exist.");
    }

    GID renderable = nextRenderable;

    renderables.emplace(renderable, Renderable(shader, mesh, texture));
    setNextRenderable();
    return renderable;
}

GID Renderer::addShader(Path vertFile, Path fragFile)
{
    try {
        return addShader(vertFile, fragFile, true);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }
}

GID Renderer::addShader(Path vertFile, Path fragFile, bool shouldLink)
{
    GID shaderID = nextShader;

    try {
        ShaderData shaderData = ShaderData(vertFile, fragFile, shouldLink);
        shaders.emplace(shaderID, shaderData);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }

    setNextShader();
    return shaderID;
}

GID Renderer::addMesh(Path meshFile) {
    try {
        return addMesh(meshFile, true);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }
}

GID Renderer::addMesh(Path meshFile, bool shouldBind) {
    GID meshID = nextMesh;

    try {
        MeshData meshData = MeshData(meshFile, shouldBind);
        meshes.emplace(meshID, meshData);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }

    setNextMesh();
    return meshID;
}

GID Renderer::addTexture(Path textureFile)
{
    try {
        return addTexture(textureFile, true);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }
}

GID Renderer::addTexture(Path textureFile, bool shouldBind)
{
    GID textureID = nextTexture;

    try {
        TextureData textureData = TextureData(textureFile, shouldBind);
        textures.emplace(textureID, textureData);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }

    setNextTexture();
    return textureID;
}

GID Renderer::addCamera()
{
    GID cameraID = nextCamera;
    cameras[cameraID] = Camera();
    setNextCamera();
    return cameraID;
}

Renderable *Renderer::getRenderable(GID rid)
{
    if (renderables.count(rid) == 0) {
        return NULL;
    }
    return &(renderables.at(rid));
}

Camera *Renderer::getCamera(GID cameraID)
{
    if (cameras.count(cameraID) == 0) {
        return NULL;
    }
    return &(cameras.at(cameraID));
}

void Renderer::setActiveCamera(GID cameraID)
{
    if (cameras.count(cameraID) == 0) {
        throw std::out_of_range("The camera does not exist.");
    }
    activeCamera = cameraID;
}

GID Renderer::getActiveCamera()
{
    return activeCamera;
}

void Renderer::destroy()
{
    renderables.clear();

    ShaderData *tmpShader;
    for (std::map<GID, ShaderData>::iterator sit = shaders.begin(); 
        sit != shaders.end(); 
        ++sit)
    {
        tmpShader = &(sit->second);
        tmpShader->destroy();
    }
    shaders.clear();
    meshes.clear();
    textures.clear();
    cameras.clear();

    activeCamera = 0;
}

void Renderer::setNextRenderable()
{
    nextRenderable++;
    if (nextRenderable != 0 && renderables.count(nextRenderable) == 0)
        return;

    GID maxTimes = 0;
    maxTimes = ~maxTimes;
    do {
        nextRenderable++;
        maxTimes--;
    } while (maxTimes > 0 && renderables.count(nextRenderable) != 0);
}

void Renderer::setNextShader()
{
    nextShader++;
    if (nextShader != 0 && shaders.count(nextShader) == 0)
        return;

    GID maxTimes = 0;
    maxTimes = ~maxTimes;
    do {
        nextShader++;
        maxTimes--;
    } while (maxTimes > 0 && shaders.count(nextShader) != 0);
}

void Renderer::setNextMesh()
{
    nextMesh++;
    if (nextMesh != 0 && meshes.count(nextMesh) == 0)
        return;

    GID maxTimes = 0;
    maxTimes = ~maxTimes;
    do {
        nextMesh++;
        maxTimes--;
    } while (maxTimes > 0 && meshes.count(nextMesh) != 0);
}

void Renderer::setNextTexture()
{
    nextTexture++;
    if (nextTexture != 0 && textures.count(nextTexture) == 0)
        return;

    GID maxTimes = 0;
    maxTimes = ~maxTimes;
    do {
        nextTexture++;
        maxTimes--;
    } while (maxTimes > 0 && textures.count(nextTexture) != 0);
}

void Renderer::setNextCamera()
{
    nextCamera++;
    if (nextCamera != 0 && cameras.count(nextCamera) == 0)
        return;

    GID maxTimes = 0;
    maxTimes = ~maxTimes;
    do {
        nextCamera++;
        maxTimes--;
    } while (maxTimes > 0 && cameras.count(nextCamera) != 0);
}

glm::mat4 Renderer::getModelMatrix(Renderable *renderable)
{
    glm::mat4 transform = glm::translate(glm::mat4(), glm::vec3(renderable->getTranslation()));

    glm::mat4 scale = glm::scale(glm::mat4(), renderable->getScale());

    glm::mat4 rotate = glm::rotate(renderable->getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
        rotate = glm::rotate(rotate, renderable->getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotate = glm::rotate(rotate, renderable->getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

    return transform * rotate * scale;
}

glm::mat4 Renderer::getViewMatrix()
{
    Camera *camera = getCamera(activeCamera);

    return glm::lookAt(
        camera->getPosition(),
        camera->getTarget(),
        camera->getUpDir()
    );
}

glm::mat4 Renderer::getProjectionMatrix()
{
    Camera *camera = getCamera(activeCamera);

    return glm::perspective(
        camera->getFOV(), 
        camera->getAspectRatio(), 
        camera->getClipNear(), 
        camera->getClipFar()
    );
}

glm::mat4 Renderer::getMVPMatrix(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
    return projection * view * model;
}
