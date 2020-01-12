#include "camera.h"

Camera::Camera(const Vec3_32b& lookFrom, const Vec3_32b& lookAt, const Vec3_32b& up, float vFov, float aspect, float aperture, float focusDisc)
{
  float theta = vFov * PI / 180.0f;
  float halfHeight = tan(theta / 2.0f);
  float halfWidth = aspect * halfHeight;

  _lensRadius = aperture / 2.0f;
  _origin = lookFrom;
  _w = (lookFrom - lookAt).normalized();
  _u = up.cross(_w).normalized();
  _v = _w.cross(_u);

  _lowerLeftCorner = _origin - halfWidth * focusDisc * _u - halfHeight * focusDisc * _v - focusDisc * _w;
  _horizontal = 2 * halfWidth * focusDisc * _u;
  _vertical = 2 * halfHeight * focusDisc * _v;
}

Vec3_32b Camera::randomInUnitDisk()
{
  Vec3_32b point;

  do
  {
    point = 2.0f * Vec3_32b(_dice.roll(), _dice.roll(), 0) - Vec3_32b(1, 1, 0);
  } while (point.dot(point) >= 1.0f);

  return point;
}

Ray Camera::getRay(float s, float t)
{
  Vec3_32b rd = _lensRadius * randomInUnitDisk();
  Vec3_32b offset = _u * rd.x + _v * rd.y;

  return Ray(_origin + offset, _lowerLeftCorner + s * _horizontal + t * _vertical - _origin - offset);
}
