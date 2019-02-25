#pragma once

class Vec3
{
public:
    Vec3() {}
    Vec3( float e0, float e1, float e2 ) {e[0] = e0; e[1] = e1; e[2] = e2; }

    const unsigned char r() const { return (unsigned char)e[0]; }
    const unsigned char g() const { return (unsigned char)e[1]; }
    const unsigned char b() const { return (unsigned char)e[2]; }

private:
    float e[3];
};