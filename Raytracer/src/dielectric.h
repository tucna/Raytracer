#pragma once

#include "material.h"
#include "ray.h"
#include "vec3.h"

class Dielectrict : public Material
{
public:
    Dielectrict(float ri) : ref_idx(ri) {}

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const;

    float schlick(float cosine, float ref_idx) const
    {
        float r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;

        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

    bool refract(const Vec3_32b& v, const Vec3_32b& n, float ni_over_nt, Vec3_32b& refracted) const
    {
        Vec3_32b uv = v.normalized();
        float dt = uv.dot(n);
        float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);

        if (discriminant > 0)
        {
            refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);

            return true;
        }
        else
            return false;
    }

    float ref_idx;
};

inline bool Dielectrict::scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const
{
    Vec3_32b outward_normal;
    Vec3_32b reflected = reflect(r_in.B, rec.normal);
    float ni_over_nt;

    attentuation = Vec3_32b(1.0, 1.0, 1.0);
    Vec3_32b refracted;

    float reflect_prob;
    float cosine;

    if (r_in.B.dot(rec.normal) > 0)
    {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * r_in.B.dot(rec.normal) / r_in.B.length();
    }
    else
    {
        outward_normal = rec.normal;
        ni_over_nt = 1.0f / ref_idx;
        cosine = -r_in.B.dot(rec.normal) / r_in.B.length();
    }
    if (refract(r_in.B, outward_normal, ni_over_nt, refracted))
    {
        //scattered = Ray(rec.p, refracted);
        reflect_prob = schlick(cosine, ref_idx);
    }
    else
    {
        scattered = Ray(rec.p, reflected);
        reflect_prob = 1.0;
    }
    if (dice.roll() < reflect_prob)
    {
        scattered = Ray(rec.p, reflected);
    }
    else
    {
        scattered = Ray(rec.p, refracted);
    }

    return true;
}
