#include <iostream>

#include "image.h"
#include "ray.h"
#include "vec3.h"

using namespace std;

template <typename T>
float hitSphere(const Vec3<T> center, float radius, const Ray<T> r)
{
    Vec3<T> oc = r.A - center;
    float a = r.B.dot(r.B);
    float b = 2.0 * oc.dot(r.B);
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

template <typename T>
Vec3<T> color(Ray<T> r)
{
    float t = hitSphere(Vec3<T>(0, 0, -1), 0.5, r);

    if (t > 0.0)
    {
        Vec3<T> temp = r.pointAtT(t) - Vec3<T>(0, 0, -1);
        Vec3<T> N = temp.normalized();
        return 0.5f * Vec3<T>(N.x + 1, N.y + 1, N.z + 1);
    }

    Vec3<T> unit_direction = r.B.normalized();
    t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * Vec3<T>(1.0, 1.0, 1.0) + t * Vec3<T>(0.5f, 0.7f, 1.0f);
}

int main(int argc, char *argv[])
{
    cout << "In progress..." << endl;

    int width = 400;
    int height = 200;

    Vec3_32b lower_left_corner(-2.0, -1.0, -1.0);
    Vec3_32b horizontal(4.0, 0.0, 0.0);
    Vec3_32b vertical(0.0, 2.0, 0.0);
    Vec3_32b origin(0.0, 0.0, 0.0);

    Image image(width, height);

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            float u = (float)x / width;
            float v = (float)y / height;

            Ray_32b r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vec3_32b col = color(r);

            //image.setPixel(x, y, Vec3_8b(col));
            //image.setPixel(x, y, Vec3_8b(255.99 * col.r, 255.99 * col.g, 255.99 * col.b));
            image.setPixel(x, height - 1 - y, Vec3_8b(255.99 * col.r, 255.99 * col.g, 255.99 * col.b));
        }
    }

    image.saveToBMP("res/output.bmp");

    return 0;
}
