#pragma once

#include "material.h"
#include "ray.h"

class Metal : public Material
{
public:
    Metal(const Vec3_32b a) : albedo(a) {}

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const;

    Vec3_32b reflect(const Vec3_32b& v, const Vec3_32b& n) const
    {
        return v - 2 * v.dot(n) * n;
    }

    Vec3_32b albedo;
};

inline bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const
{
    Vec3_32b reflected = reflect(r_in.B.normalized(), rec.normal);
    scattered = Ray(rec.p, reflected);
    attentuation = albedo;

    return (scattered.B.dot(rec.normal) > 0);
}
