#pragma once

#include "material.h"
#include "ray.h"

class Metal : public Material
{
public:
    Metal(const Vec3_32b a, float f) : albedo(a) { if (f < 1) fuzz = 1; }

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const;

    Vec3_32b reflect(const Vec3_32b& v, const Vec3_32b& n) const
    {
        return v - 2 * v.dot(n) * n;
    }

    Vec3_32b albedo;
    float fuzz;
};

inline bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const
{
    Vec3_32b reflected = reflect(r_in.B.normalized(), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * randomInUnitSphere());
    attentuation = albedo;

    return (scattered.B.dot(rec.normal) > 0);
}
