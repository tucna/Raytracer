#pragma once

#include "ray.h"

class Material;

struct HitRecord
{
    Vec3_32b point;
    Vec3_32b normal;
    Material* material;
    float t;
};

class Hitable
{
public:
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};
