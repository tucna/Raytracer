#pragma once

#include <vector>

#include "vec3.h"

class Image
{
public:
  Image(unsigned int width, unsigned int height, unsigned int channels = 3);
  ~Image();

  void setPixel(int x, int y, const Vec3_8b& color);
  void setPixel(int x, int y, const Vec3_32b& color);
  void saveToBMP(const char* file);

  unsigned int getWidth() { return _w; };
  unsigned int getHeight() { return _h; };

private:
  unsigned int _w;
  unsigned int _h;
  unsigned int _ch;

  std::vector<unsigned char> _pixels;
};
