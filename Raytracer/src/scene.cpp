#include <vector>

#include "camera.h"
#include "hitablelist.h"
#include "scene.h"
#include "sphere.h"
#include "ray.h"

#include "material.h"

Vec3_32b Scene::color(Ray r, int depth)
{
    HitRecord rec;

    if (_world->hit(r, 0.001f, FLT_MAX, rec))
    {
        Ray scattered;
        Vec3_32b attenuation;

        if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, depth + 1);
        }
        else
        {
            return Vec3_32b(0, 0, 0);
        }
    }
    else
    {
        Vec3_32b unit_direction = r.D.normalized();
        float t = 0.5f * (unit_direction.y + 1.0f);
        return (1.0f - t) * Vec3_32b(0.5f, 0.7f, 1.0f) + t * Vec3_32b(1.0, 1.0, 1.0);
    }
}

void Scene::setupDemoScene(int id)
{
    switch (id)
    {
    case 0:
    {
        std::vector<Hitable*> list;

        list.push_back(new Sphere(Vec3_32b(0, 0, -1), 0.5f, new Lambertian(Vec3_32b(0.1f, 0.2f, 0.5f))));
        list.push_back(new Sphere(Vec3_32b(0, -100.5, -1), 100.0f, new Lambertian(Vec3_32b(0.4f, 0.4f, 0.4f))));
        list.push_back(new Sphere(Vec3_32b(1, 0, -1), 0.5f, new Metal(Vec3_32b(0.8f, 0.6f, 0.2f), 0.3f)));
        list.push_back(new Sphere(Vec3_32b(-1, 0, -1), 0.5f, new Dielectrict(1.5f)));
        list.push_back(new Sphere(Vec3_32b(-1, 0, -1), -0.45f, new Dielectrict(1.5f)));

        _world = new HitableList(list);
    }

    case 1:
    {
        std::vector<Hitable*> list;

        list.push_back(new Sphere(Vec3_32b(0, 0, -1), 0.5f, new Lambertian(Vec3_32b(0.1f, 0.2f, 0.5f))));
        list.push_back(new Sphere(Vec3_32b(0, -100.5, -1), 100.0f, new Lambertian(Vec3_32b(0.4f, 0.4f, 0.4f))));
        list.push_back(new Sphere(Vec3_32b(0, 0, -105.5), 100.0f, new Metal(Vec3_32b(0.4f, 0.1f, 0.1f), 0.0f)));
        list.push_back(new Sphere(Vec3_32b(105.5, 0, 0), 100.0f, new Lambertian(Vec3_32b(0.1f, 0.4f, 0.1f))));
        list.push_back(new Sphere(Vec3_32b(1, 0, -1), 0.5f, new Metal(Vec3_32b(0.8f, 0.6f, 0.2f), 0.3f)));
        list.push_back(new Sphere(Vec3_32b(-1, 0, -1), 0.5f, new Dielectrict(1.5f)));
        list.push_back(new Sphere(Vec3_32b(-1, 0, -1), -0.45f, new Dielectrict(1.5f)));

        _world = new HitableList(list);
    }

    default:
    {}
    }
}

void Scene::render()
{
    unsigned int width = _image->getWidth();
    unsigned int height = _image->getHeight();

    for (unsigned int y = 0; y < height; y++)
    {
        for (unsigned int x = 0; x < width; x++)
        {
            Vec3_32b col(0, 0, 0);

            for (unsigned int s = 0; s < _raysPerPixel; s++)
            {
                float u = ((float)x + _dice.roll()) / (float)width;
                float v = ((float)y + _dice.roll()) / (float)height;

                Ray r = _cam->getRay(u, v);
                col = col + color(r, 0);
            }

            col = col / (float)_raysPerPixel;

            col = Vec3_32b(sqrt(col.r), sqrt(col.g), sqrt(col.b));

            _image->setPixel(x, height - 1 - y, Vec3_32b(col.r, col.g, col.b));
        }
    }

}
