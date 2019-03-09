#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "randomNumber.h"
#include "ray.h"
#include "vec3.h"

class Camera
{
public:
    Camera(Vec3_32b lookFrom, Vec3_32b lookAt, Vec3_32b up, float vfov, float aspect, float aperture, float focus_disc);

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
