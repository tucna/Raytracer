#pragma once

#include <array>

template <typename T>
struct Vec3
{
    union
    {
        std::array<T, 3> e;

        struct { T r, g, b; };
        struct { T x, y, z; };
    };

    Vec3() { e[0] = 0; e[1] = 0; e[2] = 0; }
    Vec3( T e0, T e1, T e2 ) { e[0] = e0; e[1] = e1; e[2] = e2; }

    float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    float dot(const Vec3& v) const { return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2]; }
    float squaredLength() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }


    Vec3 normalized() const { return Vec3(e[0] / length(), e[1] / length(), e[2] / length()); }
    Vec3 cross(const Vec3& v) const
    {
        return Vec3( (e[1] * v.e[2] - e[2] * v.e[1]),
                    -(e[0] * v.e[2] - e[2] * v.e[0]),
                     (e[0] * v.e[1] - e[1] * v.e[0]) );
    }

    Vec3 operator+(Vec3 v) const { return Vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]); }
    Vec3 operator-(Vec3 v) const { return Vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]); }
    Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    Vec3 operator*(Vec3 v) const { return Vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]); }
    Vec3 operator*(T s) const { return Vec3(e[0] * s, e[1] * s, e[2] * s); }
    Vec3 operator/(T s) const { return Vec3(e[0] / s, e[1] / s, e[2] / s); }
};

template <typename T>
inline Vec3<T> operator*(T s, Vec3<T> v)
{
    return v * s;
}

typedef Vec3<unsigned char> Vec3_8b;
typedef Vec3<float> Vec3_32b;
typedef Vec3<double> Vec3_64b;
