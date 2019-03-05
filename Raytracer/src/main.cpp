#include <iostream>

#include "camera.h"
#include "image.h"
#include "ray.h"
#include "vec3.h"

#include "sphere.h"
#include "hitablelist.h"

#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

#include "randomNumber.h"

using namespace std;

Vec3_32b color(Ray r, Hitable *world, int depth)
{
    HitRecord rec;

    if (world->hit(r, 0.001f, FLT_MAX, rec))
    {
        Ray scattered;
        Vec3_32b attenuation;

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return Vec3_32b(0, 0, 0);
        }
    }
    else
    {
        Vec3_32b unit_direction = r.B.normalized();
        float t = 0.5f * (unit_direction.y + 1.0f);
        return (1.0f - t) * Vec3_32b(1.0, 1.0, 1.0) + t * Vec3_32b(0.5f, 0.7f, 1.0f);
    }
}

int main(int argc, char *argv[])
{
    cout << "In progress..." << endl;

    RandomNumber mainDice;

    int width = 400;
    int height = 200;
    int ns = 100;

    Vec3_32b lookFrom(0,0,1);
    Vec3_32b lookAt(0, 0, -1);
    float dist_to_focus = (lookFrom - lookAt).length();
    float aperture = 0.05f;

    Camera cam(lookFrom, lookAt, Vec3_32b(0,1,0), 50, (float)width / (float)height, aperture, dist_to_focus);

    float R = cos(M_PI / 4.0f);

    Hitable *list[5];

    list[0] = new Sphere(Vec3_32b(0, 0, -1), 0.5f, new Lambertian(Vec3_32b(0.1f, 0.2f, 0.5f)));
    list[1] = new Sphere(Vec3_32b(0, -100.5, -1), 100.0f, new Lambertian(Vec3_32b(0.4f, 0.4f, 0.4f)));
    list[2] = new Sphere(Vec3_32b(1, 0, -1), 0.5f, new Metal(Vec3_32b(0.8f, 0.6f, 0.2f), 0.3f));
    list[3] = new Sphere(Vec3_32b(-1, 0, -1), 0.5f, new Dielectrict(1.5f));
    list[4] = new Sphere(Vec3_32b(-1, 0, -1), -0.45f, new Dielectrict(1.5f));

    Hitable *world = new HitableList(list, 5);

    Image image(width, height);

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            Vec3_32b col(0, 0, 0);

            for (int s = 0; s < ns; s++)
            {
                float u = (x + (float)mainDice.roll()) / (float)width;
                float v = (y + (float)mainDice.roll()) / (float)height;

                Ray r = cam.getRay(u, v);
                Vec3_32b p = r.pointAtT(2.0);
                col = col + color(r, world, 0);
            }

            col = col / (float)ns;

            col = Vec3_32b(sqrt(col.r), sqrt(col.g), sqrt(col.b));

            image.setPixel(x, height - 1 - y, Vec3_8b(255.99f * col.r, 255.99f * col.g, 255.99f * col.b));
        }
    }

    image.saveToBMP("res/output.bmp");

    return 0;
}
