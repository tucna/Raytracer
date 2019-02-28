#pragma once

#include "hitable.h"

class Sphere : public Hitable
{
public:
    Sphere() {}
    Sphere(Vec3_32b cen, float r, Material* mat) : center(cen), radius(r), material(mat) {}

    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;

    Vec3_32b center;
    float radius;
    Material* material;
};

inline bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    Vec3_32b oc = r.A - center;
    float a = r.B.dot(r.B);
    float b = oc.dot(r.B);
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float temp = (-b -sqrt(b * b - a * c)) / a;

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.pointAtT(rec.t);
            rec.normal = (rec.p - center) / radius;

            return true;
        }

        temp = (-b + sqrt(b * b - a * c)) / a;

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.pointAtT(rec.t);
            rec.normal = (rec.p - center) / radius;

            return true;
        }

    }

    return false;
}
