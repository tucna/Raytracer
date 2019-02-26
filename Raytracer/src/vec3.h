#pragma once

template <typename T>
struct Vec3
{
    union
    {
        T e[3];
        
        struct { T r, g, b; };
        struct { T x, y, z; };
    };

    Vec3() {}
    Vec3( T e0, T e1, T e2 ) { e[0] = e0; e[1] = e1; e[2] = e2; }
};