#pragma once

#include "vec3.h"

template <typename T>
struct Ray
{
    Ray() {}
    Ray(const Vec3<T>& origin, const Vec3<T>& direction) : A(origin), B(direction) {}

    Vec3<T> pointAtT(float t) { return A + t * B; }

    Vec3<T> A;
    Vec3<T> B;
};

typedef Ray<unsigned char> Ray_8b;
