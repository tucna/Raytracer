#pragma once

#include "hitable.h"
#include "ray.h"
#include "vec3.h"
#include "randomNumber.h"


class Material
{
public:
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const = 0;

    Vec3_32b randomInUnitSphere() const;
    Vec3_32b reflect(const Vec3_32b& v, const Vec3_32b& n) const;

protected:
    RandomNumber dice;
};

class Dielectrict : public Material
{
public:
    Dielectrict(float ri) : ref_idx(ri) {}

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const;

    float schlick(float cosine, float ref_idx) const;

    bool refract(const Vec3_32b& v, const Vec3_32b& n, float ni_over_nt, Vec3_32b& refracted) const;

private:
    float ref_idx;
};

class Lambertian : public Material
{
public:
    Lambertian(const Vec3_32b& a) : albedo(a) {}

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const;

private:
    Vec3_32b albedo;
};

class Metal : public Material
{
public:
    Metal(const Vec3_32b a, float f) : albedo(a) { fuzz = f < 1 ? f : 1; }

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const;

private:
    Vec3_32b albedo;
    float fuzz;
};
