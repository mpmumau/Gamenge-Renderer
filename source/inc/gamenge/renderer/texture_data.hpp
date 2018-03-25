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
        TextureData(Path);
        TextureData(Path, bool);
        ~TextureData();

        void bind();

        GLuint getTextureBuffer();
        unsigned long long int getNumPixels();
    private:
        GLuint textureBufferID;
        unsigned long long int numPixels;
        unsigned char *data;
        unsigned int imageWidth, imageHeight;

        void init();
        void load(Path, bool);
    };

} // end namespace Gamenge

#endif