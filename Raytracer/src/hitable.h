#pragma once

#include "ray.h"

class Material;

struct HitRecord
{
    float t;
    Vec3_32b p;
    Vec3_32b normal;
    Material* mat_ptr;
};

class Hitable
{
public:
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};
