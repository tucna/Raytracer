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
