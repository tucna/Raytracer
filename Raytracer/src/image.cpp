#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT

#include "image.h"
#include "stb_image_write.h"
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

void Image::setPixel(int x, int y, const Vec3_32b& color)
{
  Vec3_8b vec;

  vec.r = static_cast<unsigned char>(round(255.0f * color.r));
  vec.g = static_cast<unsigned char>(round(255.0f * color.g));
  vec.b = static_cast<unsigned char>(round(255.0f * color.b));

  setPixel(x, y, vec);
}

void Image::saveToBMP(const char* file)
{
  stbi_write_bmp(file, _w, _h, _ch, _pixels.data());
}
