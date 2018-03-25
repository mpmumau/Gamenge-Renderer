#ifndef GAMENGE_RENDERER_MESH_DATA_H
#define GAMENGE_RENDERER_MESH_DATA_H

#include <GL/glew.h>

/* Application headers */
#include <gamenge/common/common.hpp>

using namespace Gamenge;

namespace Gamenge {

    class MeshData {
    public:
        MeshData(Path);
        MeshData(Path, bool);

        void bind();

        unsigned int getNumVertices();
        unsigned int getNumNormals();
        unsigned int getNumUvs();
        unsigned int getNumIndices();

        GLuint getVertexBuffer();
        GLuint getNormalBuffer();
        GLuint getUVBuffer();
        GLuint getIndexBuffer();
    private:
        unsigned int numVertices, numNormals, numUvs, numIndices;
        GLuint glVertexBufferID, glNormalBufferID, glUVBufferID, glIndexBufferID;

        GLfloat *vertices;
        GLfloat *normals;
        GLfloat *uvs;
        unsigned int *indices;

        void load(Path, bool);
        void setDefaults();
    };

} // end namespace Gamenge

#endif