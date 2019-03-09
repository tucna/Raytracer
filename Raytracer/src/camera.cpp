#include "camera.h"

Camera::Camera(Vec3_32b lookFrom, Vec3_32b lookAt, Vec3_32b up, float vfov, float aspect, float aperture, float focus_disc)
{
    _lensRadius = aperture / 2.0f;
    float theta = vfov * M_PI / 180.0f;
    float half_height = tan(theta / 2.0f);
    float half_width = aspect * half_height;

    _origin = lookFrom;
    _w = (lookFrom - lookAt).normalized();
    _u = up.cross(_w).normalized();
    _v = _w.cross(_u);

    _lowerLeftCorner = _origin - half_width * focus_disc * _u - half_height * focus_disc * _v - focus_disc * _w;
    _horizontal = 2 * half_width * focus_disc * _u;
    _vertical = 2 * half_height * focus_disc * _v;
}

Vec3_32b Camera::randomInUnitDisk()
{
    Vec3_32b p;

    do
    {
        p = 2.0f * Vec3_32b(_dice.roll(), _dice.roll(), 0) - Vec3_32b(1, 1, 0);
    } while (p.dot(p) >= 1.0f);

    return p;
}

Ray Camera::getRay(float s, float t)
{
    Vec3_32b rd = _lensRadius * randomInUnitDisk();
    Vec3_32b offset = _u * rd.x + _v * rd.y;

    return Ray(_origin + offset, _lowerLeftCorner + s * _horizontal + t * _vertical - _origin - offset);
}
