#include <iostream>

#include "image.h"
#include "vec3.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "In progress..." << endl;

    int width = 640;
    int height = 480;

    Image image(width, height);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            image.SetPixel(x, y, Vec3<unsigned char>(255, 0, 255));
        }
    }

    image.SaveToBMP("res/output.bmp");

    return 0;
}