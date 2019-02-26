#pragma once

#include <vector>

#include "vec3.h"

class Image
{
public:
    Image(unsigned int width, unsigned int height, unsigned int channels = 3);
    ~Image();

    void SetPixel(int x, int y, const Vec3<unsigned char>& color);
    void SaveToBMP(const char* file);

private:
    unsigned int _w;
    unsigned int _h;
    unsigned int _ch;

    std::vector<unsigned char> _pixels;
};