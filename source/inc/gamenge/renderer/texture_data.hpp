#ifndef GAMENGE_RENDERER_TEXTURE_DATA_H
#define GAMENGE_RENDERER_TEXTURE_DATA_H

/* Library headers */
#include <string>
#include <GL/glew.h>

/* Application headers */
#include <gamenge/common/common.hpp>

using namespace Gamenge;

namespace Gamenge {

    class TextureData
    {
    public:
        /**
         * @brief  Construct a texture from the provided BMP image file path, and immediately load it into OpenGL.
         *
         * @param[in]  filename  The BMP from which to load the texture.
         * 
         * @throw  std::invalid_argument  If the given path is null or empty.
         * @throw  std::runtime_error  If there was an error loading the file, or with OpenGL calls.
         */
        TextureData(Path);

        /**
         * @brief  Construct a texture from the provided BMP image file path, and, optionally, immediately load it into OpenGL.
         *
         * @param[in]  filename  The BMP from which to load the texture.
         * @param[in]  shouldBind  Whether or not to immediately load the texture into OpenGL.
         * 
         * @throw  std::invalid_argument  If the given path is null or empty.
         * @throw  std::runtime_error  If there was an error loading the file, or with OpenGL calls.
         */
        TextureData(Path, bool);

        /**
         * @brief  Copy constructor.
         *
         * @param[in]  rhs  The TextureData object to copy.
         */
        TextureData(const TextureData&);

        /**
         * @brief  Destroy the texture data and release its resources.
         */
        ~TextureData();

        /**
         * @brief  Bind the texture in OpenGL if has not already been bound.
         */
        void bind();

        /**
         * @brief  Get the OpenGL ID of the bound texture buffer.
         *
         * @return  The OpenGL texture buffer ID.
         */
        GLuint getTextureBuffer();

        /**
         * @brief  Gets the number of pixel data elements in the texture buffer.
         *
         * @return  The number of pixel data elements (each pixel has 3!)
         */
        unsigned long long int getNumPixels();
    private:
        GLuint textureBufferID;
        unsigned long long int numPixels;
        unsigned char *data;
        unsigned int imageWidth, imageHeight;
        bool isBound;

        void init();
        void load(Path, bool);
    };

} // end namespace Gamenge

#endif