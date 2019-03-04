#pragma once

#include "hitable.h"
#include "ray.h"
#include "vec3.h"
#include "randomNumber.h"


class Material
{
public:
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const = 0;

    Vec3_32b randomInUnitSphere() const
    {
        Vec3_32b p;

        do
        {
            p = 2.0f * Vec3_32b(dice.roll(), dice.roll(), dice.roll()) - Vec3_32b(1, 1, 1);
            //p = 2.0f * Vec3_32b(0.1f, 0.1f, 0.1f) - Vec3_32b(1, 1, 1);
        } while (p.squaredLength() >= 1.0);

        return p;
    }

    RandomNumber dice;
};
