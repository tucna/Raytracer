#pragma once

#include "hitable.h"

class Sphere : public Hitable
{
public:
    Sphere() {}
    Sphere(Vec3_32b center, float radius, Material* material) :
		_center(center), _radius(radius), _material(material) {}

    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const;

private:
    Vec3_32b _center;
    float _radius;
    Material* _material;
};

inline bool Sphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const
{
    Vec3_32b oc = r.O - _center;

    float a = r.D.dot(r.D);
    float b = oc.dot(r.D);
    float c = oc.dot(oc) - _radius * _radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float temp = (-b -sqrt(b * b - a * c)) / a;

        if (temp < tMax && temp > tMin)
        {
            rec.t = temp;
            rec.p = r.pointAtT(rec.t);
            rec.normal = (rec.p - _center) / _radius;
            rec.mat_ptr = _material;

            return true;
        }

        temp = (-b + sqrt(b * b - a * c)) / a;

        if (temp < tMax && temp > tMin)
        {
            rec.t = temp;
            rec.p = r.pointAtT(rec.t);
            rec.normal = (rec.p - _center) / _radius;
            rec.mat_ptr = _material;

            return true;
        }
    }

    return false;
}
