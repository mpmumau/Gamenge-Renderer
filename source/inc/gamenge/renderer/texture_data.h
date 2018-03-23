#ifndef GAMENGE_RENDERER_TEXTURE_DATA_H
#define GAMENGE_RENDERER_TEXTURE_DATA_H

/* Library headers */
#include <string>
#include <GL/glew.h>
#include <GL/glu.h>

/* Application headers */
#include <gamenge/common/common.h>

using namespace Gamenge;

namespace Gamenge {

    class TextureData
    {
    public:
        TextureData();
        TextureData(Path);

        GLuint getTextureBuffer();
        unsigned long long int getNumPixels();
    private:
        GLuint textureBufferID;
        unsigned long long int numPixels;

        void loadBitmap(Path);
    };

} // end namespace Gamenge

#endif