#pragma once

#define _USE_MATH_DEFINES // for C++
#include <math.h>

#include "ray.h"
#include "vec3.h"

class Camera
{
public:
    Camera(Vec3_32b lookFrom, Vec3_32b lookAt, Vec3_32b up, float vfov, float aspect)
    {
        Vec3_32b u, v, w;

        float theta = vfov * M_PI / 180;
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;

        origin = lookFrom;
        w = (lookFrom - lookAt).normalized();
        u = up.cross(w).normalized();
        v = w.cross(u);

        lower_left_corner = origin - half_width * u - half_height * v - w;
        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
        //origin = Vec3_32b(0.0, 0.0, 0.0);
    }

    Ray getRay(float u, float v) { return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }

private:
    Vec3_32b lower_left_corner;
    Vec3_32b horizontal;
    Vec3_32b vertical;
    Vec3_32b origin;
};
