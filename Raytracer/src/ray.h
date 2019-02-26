#pragma once

#include "vec3.h"

template <typename T>
struct Ray
{
    Ray() {}
    Ray(const Vec3<T>& beg, const Vec3<T>& end) : A(beg), B(end) {}

    Vec3<T> PointAtT(float t) { return (1 - t) * A + t * B; }

    Vec3<T> A;
    Vec3<T> B;
};

typedef Ray<unsigned char> Ray_8b;
