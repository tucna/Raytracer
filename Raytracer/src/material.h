#pragma once

#include "hitable.h"
#include "ray.h"
#include "vec3.h"

class Material
{
public:
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const = 0;
};
