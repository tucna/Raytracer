#pragma once

#include "hitable.h"

template <typename T>
class Sphere : public Hitable<T>
{
public:
    Sphere() {}
    Sphere(Vec3<T> cen, float r) : center(cen), radius(r) {}

    virtual bool hit(const Ray<T>& r, float t_min, float t_max, HitRecord<T>& rec) const;

    Vec3<T> center;
    float radius;
};

template<typename T>
inline bool Sphere<T>::hit(const Ray<T>& r, float t_min, float t_max, HitRecord<T>& rec) const
{
    Vec3<T> oc = r.A - center;
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
