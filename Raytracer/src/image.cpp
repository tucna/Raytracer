#define _CRT_SECURE_NO_DEPRECATE

#include "image.h"
#include "vec3.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(unsigned int width, unsigned int height, unsigned int channels) :
    _w(width),
    _h(height),
    _ch(channels)
{
    _pixels.resize(width * height * channels);
}

Image::~Image()
{
    _pixels.clear();
}

void Image::SetPixel(int x, int y, const Vec3<unsigned char>& color)
{
    unsigned int index = (y * _w + x) * _ch;

    _pixels[index + 0] = color.r;
    _pixels[index + 1] = color.g;
    _pixels[index + 2] = color.b;
}

void Image::SaveToBMP(const char* file)
{
    stbi_write_bmp(file, _w, _h, _ch, _pixels.data());
}
