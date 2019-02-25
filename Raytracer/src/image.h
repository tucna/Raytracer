#pragma once

#include <vector>

#include "vec3.h"

class Image
{
public:
    Image(unsigned int width, unsigned int height);
    ~Image();

    void SetPixel(int x, int y, const Vec3& color);
    void SaveToBMP(const char* file);

private:
    unsigned int _w;
    unsigned int _h;

    std::vector<unsigned char> _pixels;
};