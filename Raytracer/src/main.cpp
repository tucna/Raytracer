#include <iostream>
#include <random>

#include "camera.h"
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
    int ns = 100;

    Hitable<float> *list[2];

    list[0] = new Sphere<float>(Vec3_32b(0, 0, -1), 0.5);
    list[1] = new Sphere<float>(Vec3_32b(0, -100.5, -1), 100);

    Hitable<float> *world = new HitableList<float>(list, 2);
    Camera cam;

    Image image(width, height);

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            Vec3_32b col(0, 0, 0);

            for (int s = 0; s < ns; s++)
            {
                float u = (x + dist(rng)) / (float)width;
                float v = (y + dist(rng)) / (float)height;

                Ray_32b r = cam.getRay(u, v);
                Vec3_32b p = r.pointAtT(2.0);
                col = col + color(r, world);
            }

            col = col / (float)ns;
            image.setPixel(x, height - 1 - y, Vec3_8b(255.99 * col.r, 255.99 * col.g, 255.99 * col.b));
        }
    }

    image.saveToBMP("res/output.bmp");

    return 0;
}
