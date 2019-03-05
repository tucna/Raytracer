#pragma once

#include "material.h"
#include "ray.h"

class Lambertian : public Material
{
public:
    Lambertian(const Vec3_32b& a) : albedo(a) {}

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const;

    Vec3_32b albedo;
};

inline bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const
{
    Vec3_32b target = rec.p + rec.normal + randomInUnitSphere();
    scattered = Ray(rec.p, target - rec.p);
    attentuation = albedo;

    return true;
}
