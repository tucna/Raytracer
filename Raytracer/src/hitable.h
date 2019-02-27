#pragma once

#include "ray.h"

template <typename T>
struct HitRecord
{
    float t;
    Vec3<T> p;
    Vec3<T> normal;
};

template <typename T>
class Hitable
{
public:
    virtual bool hit(const Ray<T>& r, float t_min, float t_max, HitRecord<T>& rec) const = 0;
};