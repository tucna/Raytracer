#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

struct RGBType {
    unsigned char r;
    unsigned char g;
    unsigned char b;

    RGBType(unsigned char rr, unsigned char gg, unsigned char bb) : r(rr), g(gg), b(bb) {}
};

int main(int argc, char *argv[])
{
    cout << "In progress..." << endl;

    int width = 640;
    int height = 480;

    vector<RGBType> pixels;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            pixels.push_back(RGBType(255, 0, 0));
        }
    }

    stbi_write_bmp("res/output.bmp", width, height, 3, pixels.data());

    return 0;
}