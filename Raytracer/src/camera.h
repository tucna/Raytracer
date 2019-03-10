#pragma once

#include "randomNumber.h"
#include "ray.h"
#include "vec3.h"

constexpr float PI = 3.14159265359f;

class Camera
{
public:
    Camera(const Vec3_32b& lookFrom, const Vec3_32b& lookAt, const Vec3_32b& up, float vFov, float aspect, float aperture, float focus_disc);

    Vec3_32b randomInUnitDisk();
    Ray getRay(float s, float t);

private:
    Vec3_32b _lowerLeftCorner;
    Vec3_32b _horizontal;
    Vec3_32b _vertical;
    Vec3_32b _origin;
    Vec3_32b _u;
	Vec3_32b _v;
	Vec3_32b _w;

    float _lensRadius;

    RandomNumber _dice;
};
