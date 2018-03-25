#ifndef GAMENGE_RENDERER_MESH_DATA_H
#define GAMENGE_RENDERER_MESH_DATA_H

#include <GL/glew.h>

/* Application headers */
#include <gamenge/common/common.hpp>

using namespace Gamenge;

namespace Gamenge {

    class MeshData {
    public:
        /**
         * @brief  Construct a mesh data object, and immediately load it in OpenGL.
         *
         * @param[in]  meshFile  The mesh file to load.
         * 
         * @throw  std::invalid_argument  If the path given is null or empty.
         * @throw  std::runtime_error  If there was an error loading the file, or with OpenGL calls.
         */
        MeshData(Path);

        /**
         * @brief  Construct a mesh data object, and, optionally, immediately load it in OpenGL.
         *
         * @param[in]  meshFile  The mesh file to load.
         * @param[in]  shouldBind  Whether or not to immediately load the mesh in OpenGL.
         * 
         * @throw  std::invalid_argument  If the path given is null or empty.
         * @throw  std::runtime_error  If there was an error loading the file, or with OpenGL calls.
         */
        MeshData(Path, bool);

        /**
         * @brief  Bind the mesh's data in OpenGL, if it has not already been bound.
         */
        void bind();

        /**
         * @brief  Get the number of vertice floats in the mesh data.
         *
         * @return  The number of vertice floats.
         */
        unsigned int getNumVertices();

        /**
         * @brief  Get the number of normal floats in the mesh data.
         *
         * @return  The number of normal floats.
         */
        unsigned int getNumNormals();

        /**
         * @brief  Get the number of UV floats in the mesh data.
         *
         * @return  The number of UV floats.
         */
        unsigned int getNumUvs();

        /**
         * @brief  Get the number of index ints in the mesh data.
         *
         * @return  The number of index ints.
         */
        unsigned int getNumIndices();

        /**
         * @brief  Get the OpenGL ID of the vertex buffer.
         *
         * @return  The OpenGL ID of the vertex buffer.
         */
        GLuint getVertexBuffer();

        /**
         * @brief  Get the OpenGL ID of the normal buffer.
         *
         * @return  The OpenGL ID of the normal buffer.
         */
        GLuint getNormalBuffer();

        /**
         * @brief  Get the OpenGL ID of the UV buffer.
         *
         * @return  The OpenGL ID of the UV buffer.
         */
        GLuint getUVBuffer();

        /**
         * @brief  Get the OpenGL ID of the index buffer.
         *
         * @return  The OpenGL ID of the index buffer.
         */
        GLuint getIndexBuffer();
    private:
        unsigned int numVertices, numNormals, numUvs, numIndices;
        GLuint glVertexBufferID, glNormalBufferID, glUVBufferID, glIndexBufferID;

        GLfloat *vertices;
        GLfloat *normals;
        GLfloat *uvs;
        unsigned int *indices;
        bool isBound;

        void load(Path, bool);
        void setDefaults();
    };

} // end namespace Gamenge

#endif