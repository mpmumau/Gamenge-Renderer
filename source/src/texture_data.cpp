/* Library headers */
#include <stdexcept>
#include <string.h>
#include <GL/glew.h>

/* Application headers */
#include <gamenge/common/common.hpp>

/* Self header */
#include <gamenge/renderer/texture_data.hpp>

using namespace Gamenge;

TextureData::TextureData(Path filename)
{
    init();
    try {
        load(filename, true);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }
}

TextureData::TextureData(Path filename, bool shouldBind)
{
    init();
    try {
        load(filename, shouldBind);
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch(const std::runtime_error& e) {
        throw e;
    }
}

TextureData::~TextureData()
{
    if (data != NULL) {
        delete[] data;
    }
}

void TextureData::bind()
{
    glLogicOp(GL_COPY_INVERTED);
    glEnable(GL_COLOR_LOGIC_OP);

    glGenTextures(1, &textureBufferID);
    glBindTexture(GL_TEXTURE_2D, getTextureBuffer());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glLogicOp(GL_COPY);
    glDisable(GL_COLOR_LOGIC_OP);

    delete [] data;
    data = NULL;

    // trilinear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // trilinear filtering requires mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
}

GLuint TextureData::getTextureBuffer()
{
    return textureBufferID;
}

unsigned long long int TextureData::getNumPixels()
{
    return numPixels;
}

void TextureData::init()
{
    textureBufferID = 0;
    numPixels = 0;
    data = NULL;
    imageWidth = 0;
    imageHeight = 0;
}

void TextureData::load(Path bmpFile, bool shouldBind)
{
    if (bmpFile == NULL) {
        throw std::invalid_argument("Supplied file path was null.");
    }

    if (strlen(bmpFile) == 0) {
        throw std::invalid_argument("Supplied file path was an empty string.");
    }

    FILE *file = fopen(bmpFile, "rb");
    if (!file) {
        throw std::runtime_error("Bitmap file was not a valid file path.");
    }

    const unsigned int sizeOfBmpHeader = 54;

    unsigned char header[sizeOfBmpHeader];
    unsigned int dataPos;
    unsigned long long int imageSize;

    if (fread(header, 1, sizeOfBmpHeader, file) != sizeOfBmpHeader) {
        throw std::runtime_error("Bitmap file was too small; is it corrupt?");
    }

    if (header[0] != 'B' || header[1] != 'M') {
        throw std::runtime_error("Bitmap file does not start with characters \"BM\"");
    }
    
    
    if (*(int *)&(header[0x1E]) != 0) { // Bitmap compression: 0=none, 1=RLE-8, 2=RLE-4
        throw std::runtime_error("Bitmap compression type is incorrect; should be none.");
    }

    if (*(int *)&(header[0x1C]) != 24) { // number of bits per pixel (1, 4, 8, or 24)
        throw std::runtime_error("Bitmap file was not 24 bit.");
    }

    dataPos = *(int *)&(header[0x0A]);
    imageSize = *(int *)&(header[0x22]);
    imageWidth = *(int *)&(header[0x12]);
    imageHeight = *(int *)&(header[0x16]);

    if (imageSize == 0) {
        imageSize = 3 * (imageWidth * imageHeight);
    }

    if (dataPos == 0) {
        dataPos = sizeOfBmpHeader;
    }

    numPixels = imageSize;

    data = new unsigned char[numPixels];
    fread(data, 1, imageSize, file);

    fclose(file);

    if (shouldBind) {
        bind();
    }
}
