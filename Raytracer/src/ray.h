#pragma once

#include "vec3.h"

struct Ray
{
    Ray() {}
    Ray(const Vec3_32b& origin, const Vec3_32b& direction) : A(origin), B(direction) {}

    Vec3_32b pointAtT(float t) const { return A + t * B; }

    Vec3_32b A;
    Vec3_32b B;
};
