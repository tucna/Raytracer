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
    Vec3_32b lower_left_corner;
    Vec3_32b horizontal;
    Vec3_32b vertical;
    Vec3_32b origin;

    Vec3_32b u, v, w;
    float lens_radius;

    RandomNumber dice;
};
