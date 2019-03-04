/*
#include <random>
#include <time.h>
#include <iostream>
class enemy {
private:
    std::random_device rd;
    int max_roll;
    typedef std::mt19937 MyRng;
    MyRng rng;
    std::uniform_int_distribution<int> dice;
public:
    enemy(int MR) : max_roll(MR), rng(rd()), dice(std::uniform_int_distribution<>(1, MR)) {
        rng.seed(::time(NULL));
    }

    int roll() {
        return dice(rng);
    }
};

int main()
{
    enemy en(6);
    std::cout << "Roll dice produced : " << en.roll() << std::endl;
    return 0;
}
*/

#pragma once

#include "randomNumber.h"

#include "material.h"
#include "ray.h"

class Lambertian : public Material
{
public:
    Lambertian(const Vec3_32b& a) : albedo(a) {}

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const;

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

    Vec3_32b albedo;
    RandomNumber dice;
};

inline bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const
{
    Vec3_32b target = rec.p + rec.normal + randomInUnitSphere();
    scattered = Ray(rec.p, target - rec.p);
    attentuation = albedo;

    return true;
}
