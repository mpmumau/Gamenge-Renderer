/* Library Headers */
#include <GL/glew.h>
#include <GL/glu.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

/* Application headers */
#include <gamenge/common/common.h>

/* Self header */
#include <gamenge/renderer/mesh_data.h>

using namespace Gamenge;

MeshData::MeshData()
{
    setDefaults();
}

MeshData::MeshData(Path meshFile)
{
    setDefaults();
    loadFromFile(meshFile);
}

unsigned int MeshData::getNumVertices()
{
    return numVertices;
}

unsigned int MeshData::getNumNormals()
{
    return numNormals;
}

unsigned int MeshData::getNumUvs()
{
    return numUvs;
}

unsigned int MeshData::getNumIndices()
{
    return numIndices;
}

GLuint MeshData::getVertexBuffer()
{
    return glVertexBufferID;
}

GLuint MeshData::getNormalBuffer()
{
    return glNormalBufferID;
}

GLuint MeshData::getUVBuffer()
{
    return glUVBufferID;
}

GLuint MeshData::getIndexBuffer()
{
    return glIndexBufferID;
}

void MeshData::loadFromFile(Path meshFile)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(meshFile, 0);
    if (!scene || scene->mNumMeshes < 1) {
        // Todo: Throw an exception. Mesh file contains no meshes.
        exit(1);
    }

    aiMesh *mesh = scene->mMeshes[0];

    GLfloat *vertices = NULL;
    if (mesh->HasPositions()) {
        vertices = new GLfloat[mesh->mNumVertices * 3];
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            vertices[i * 3] = mesh->mVertices[i].x;
            vertices[i * 3 + 1] = mesh->mVertices[i].y;
            vertices[i * 3 + 2] = mesh->mVertices[i].z;
            
            numVertices += 3;
        }
    }

    GLfloat *normals = NULL;
    if (mesh->HasNormals()) {
        normals = new GLfloat[mesh->mNumVertices * 3];
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            normals[i * 3] = mesh->mNormals[i].x;
            normals[i * 3 + 1] = mesh->mNormals[i].y;
            normals[i * 3 + 2] = mesh->mNormals[i].z;
            
            numNormals += 3;
        }
    }

    GLfloat *uvs = NULL;
    if (mesh->HasTextureCoords(0)) {
        uvs = new GLfloat[mesh->mNumVertices * 2];
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            uvs[(i * 2)] = mesh->mTextureCoords[0][i].x;
            uvs[(i * 2) + 1] = mesh->mTextureCoords[0][i].y;
            
            numUvs += 2;
        }
    }

    unsigned int *indices = NULL;
    if (mesh->HasFaces()) {
        indices = new unsigned int[mesh->mNumFaces * 3];
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            indices[i * 3] = mesh->mFaces[i].mIndices[0];
            indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
            indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
            
            numIndices += 3;
        }
    }

    glGenBuffers(1, &glVertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->getVertexBuffer());
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->getNumVertices(), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &glUVBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->getUVBuffer());
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->getNumUvs(), uvs, GL_STATIC_DRAW);

    glGenBuffers(1, &glNormalBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->getNormalBuffer());
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->getNumNormals(), normals, GL_STATIC_DRAW);

    // Todo: Bind index buffer.

    delete[] vertices;
    delete[] normals;
    delete[] uvs;
    delete[] indices;
}

void MeshData::setDefaults()
{
    numVertices = 0;
    numNormals = 0;
    numUvs = 0;
    numIndices = 0;

    glVertexBufferID = 0;
    glNormalBufferID = 0;
    glUVBufferID = 0;
    glIndexBufferID = 0;
}