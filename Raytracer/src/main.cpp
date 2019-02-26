#include <iostream>

#include "image.h"
#include "ray.h"
#include "vec3.h"

using namespace std;

template <typename T>
Vec3<T> color(const Ray<T>& r)
{
    Vec3<T> unit_direction = r.B.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * Vec3<T>(1.0, 1.0, 1.0) + t * Vec3<T>(0.5f, 0.7f, 1.0f);
}

int main(int argc, char *argv[])
{
    cout << "In progress..." << endl;

    int width = 200;
    int height = 100;

    Vec3<float> lower_left_corner(-2.0, -1.0, -1.0);
    Vec3<float> horizontal(4.0, 0.0, 0.0);
    Vec3<float> vertical(0.0, 2.0, 0.0);
    Vec3<float> origin(0.0, 0.0, 0.0);

    Image image(width, height);

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            float u = (float)x / width;
            float v = (float)y / height;

            Ray<float> r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vec3<float> col = color(r);

            image.setPixel(x, y, Vec3_8b(255.99 * col.r, 255.99 * col.g, 255.99 * col.b));
        }
    }

    image.saveToBMP("res/output.bmp");

    return 0;
}
