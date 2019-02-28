#pragma once

#include "ray.h"
#include "vec3.h"

class Camera
{
public:
    Camera() 
    {
        lower_left_corner = Vec3_32b(-2.0, -1.0, -1.0);
        horizontal = Vec3_32b(4.0, 0.0, 0.0);
        vertical = Vec3_32b(0.0, 2.0, 0.0);
        origin = Vec3_32b(0.0, 0.0, 0.0);
    }

    Ray getRay(float u, float v) { return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }

private:
    Vec3_32b lower_left_corner;
    Vec3_32b horizontal;
    Vec3_32b vertical;
    Vec3_32b origin;
};
