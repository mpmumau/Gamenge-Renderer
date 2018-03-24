/* Library headers */
#include <GL/glew.h>

/* Application headers */
#include <gamenge/common/common.hpp>

/* Self header */
#include <gamenge/renderer/texture_data.hpp>

using namespace Gamenge;

TextureData::TextureData()
{
    textureBufferID = 0;
    numPixels = 0;
}

TextureData::TextureData(Path filename)
{
    textureBufferID = 0;
    numPixels = 0;

    loadBitmap(filename);
}

GLuint TextureData::getTextureBuffer()
{
    return textureBufferID;
}

unsigned long long int TextureData::getNumPixels()
{
    return numPixels;
}

void TextureData::loadBitmap(Path bmpFile)
{
    FILE *file = fopen(bmpFile, "rb");
    if (!file) {
        // Todo: Throw exception. File couldn't be opened.
        exit(1);
    }

    unsigned int sizeOfBmpHeader = 54;
    unsigned char header[sizeOfBmpHeader];
    unsigned int dataPos, width, height;
    unsigned char *data;
    unsigned long long int imageSize;

    if (fread(header, 1, sizeOfBmpHeader, file) != sizeOfBmpHeader) {
        // Todo: Throw exception. File too short.
        fclose(file);
        exit(1);
    }

    if (header[0] != 'B' || header[1] != 'M') {
        // Todo: Throw exception. File does not start with BM as expected.
        fclose(file);
        exit(1);
    }
    
    
    if (*(int *)&(header[0x1E]) != 0) { // Bitmap compression: 0=none, 1=RLE-8, 2=RLE-4
        // Todo: Throw exception. Bitmap compression type incorrect; use no compression.
        fclose(file);
        exit(1);
    }

    if (*(int *)&(header[0x1C]) != 24) { // number of bits per pixel (1, 4, 8, or 24)
        // Todo: Throw exception. Bitmap is not 24 bits per pixel.
        fclose(file);
        exit(1);
    }

    dataPos    = *(int *)&(header[0x0A]);
    imageSize  = *(int *)&(header[0x22]);
    width      = *(int *)&(header[0x12]);
    height     = *(int *)&(header[0x16]);

    if (imageSize == 0) {
        imageSize = 3 * (width * height);
    }

    if (dataPos == 0) {
        dataPos = 54;
    }

    numPixels = imageSize;

    data = new unsigned char[numPixels];
    fread(data, 1, imageSize, file);
    fclose(file);

    glLogicOp(GL_COPY_INVERTED);
    glEnable(GL_COLOR_LOGIC_OP);

    glGenTextures(1, &textureBufferID);
    glBindTexture(GL_TEXTURE_2D, getTextureBuffer());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glLogicOp(GL_COPY);
    glDisable(GL_COLOR_LOGIC_OP);

    delete [] data;

    // trilinear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // trilinear filtering requires mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
}