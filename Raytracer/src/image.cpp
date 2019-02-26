#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

#include "image.h"
#include "vec3.h"

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

void Image::setPixel(int x, int y, const Vec3_8b& color)
{
    unsigned int index = (y * _w + x) * _ch;

    _pixels[index + 0] = color.r;
    _pixels[index + 1] = color.g;
    _pixels[index + 2] = color.b;
}

void Image::saveToBMP(const char* file)
{
    stbi_write_bmp(file, _w, _h, _ch, _pixels.data());
}
