#pragma once

#include "vec3.h"

struct Ray
{
  Ray() {}
  Ray(const Vec3_32b& origin, const Vec3_32b& direction) : O(origin), D(direction) {}

  Vec3_32b pointAtT(float t) const { return O + t * D; }

  // Ray origin
  Vec3_32b O;
  // Ray direction
  Vec3_32b D;
};
