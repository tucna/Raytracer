#include <iostream>

#include "image.h"
#include "ray.h"
#include "vec3.h"

#include "sphere.h"
#include "hitablelist.h"

using namespace std;

template <typename T>
Vec3<T> color(Ray<T> r, Hitable<T> *world)
{
    HitRecord<T> rec;

    if (world->hit(r, 0.0, FLT_MAX, rec))
    {
        return 0.5f * Vec3<T>(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);
    }
    else
    {
        Vec3<T> unit_direction = r.B.normalized();
        float t = 0.5f * (unit_direction.y + 1.0f);
        return (1.0f - t) * Vec3<T>(1.0, 1.0, 1.0) + t * Vec3<T>(0.5f, 0.7f, 1.0f);
    }
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

    Hitable<float> *list[2];

    list[0] = new Sphere<float>(Vec3_32b(0, 0, -1), 0.5);
    list[1] = new Sphere<float>(Vec3_32b(0, -100.5, -1), 100);

    Hitable<float> *world = new HitableList<float>(list, 2);

    Image image(width, height);

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            float u = (float)x / width;
            float v = (float)y / height;

            Ray_32b r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vec3_32b p = r.pointAtT(2.0);
            Vec3_32b col = color(r, world);

            image.setPixel(x, height - 1 - y, Vec3_8b(255.99 * col.r, 255.99 * col.g, 255.99 * col.b));
        }
    }

    image.saveToBMP("res/output.bmp");

    return 0;
}
