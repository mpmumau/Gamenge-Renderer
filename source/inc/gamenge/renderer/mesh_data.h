#ifndef GAMENGE_RENDERER_MESH_DATA_H
#define GAMENGE_RENDERER_MESH_DATA_H

#include <GL/glew.h>
#include <GL/glu.h>

/* Application headers */
#include <gamenge/common/common.h>

using namespace Gamenge;

namespace Gamenge {

    class MeshData {
    public:
        MeshData();
        MeshData(Path);

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

        void loadFromFile(Path);
        void setDefaults();
    };

} // end namespace Gamenge

#endif