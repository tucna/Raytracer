#include "camera.h"

Camera::Camera(Vec3_32b lookFrom, Vec3_32b lookAt, Vec3_32b up, float vfov, float aspect, float aperture, float focus_disc)
{
    lens_radius = aperture / 2.0f;
    float theta = vfov * M_PI / 180.0f;
    float half_height = tan(theta / 2.0f);
    float half_width = aspect * half_height;

    origin = lookFrom;
    w = (lookFrom - lookAt).normalized();
    u = up.cross(w).normalized();
    v = w.cross(u);

    lower_left_corner = origin - half_width * focus_disc * u - half_height * focus_disc * v - focus_disc * w;
    horizontal = 2 * half_width * focus_disc * u;
    vertical = 2 * half_height * focus_disc * v;
}

Vec3_32b Camera::randomInUnitDisk()
{
    Vec3_32b p;

    do
    {
        p = 2.0f * Vec3_32b(dice.roll(), dice.roll(), 0) - Vec3_32b(1, 1, 0);
    } while (p.dot(p) >= 1.0f);

    return p;
}

Ray Camera::getRay(float s, float t)
{
    Vec3_32b rd = lens_radius * randomInUnitDisk();
    Vec3_32b offset = u * rd.x + v * rd.y;

    return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}
