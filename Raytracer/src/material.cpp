#include "material.h"

Vec3_32b Material::randomPointInUnitSphere() const
{
  Vec3_32b point;

  do
  {
    point = 2.0f * Vec3_32b(dice.roll(), dice.roll(), dice.roll()) - Vec3_32b(1, 1, 1);
  } while (point.squaredLength() >= 1.0);

  return point;
}

Vec3_32b Material::reflect(const Vec3_32b& v, const Vec3_32b& n) const
{
  return v - 2 * v.dot(n) * n;
}

float Material::schlick(float cosine, float ref_idx) const
{
  float r0 = (1 - ref_idx) / (1 + ref_idx);

  r0 = r0 * r0;

  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Material::refract(const Vec3_32b& v, const Vec3_32b& n, float niOverNt, Vec3_32b& refracted) const
{
  Vec3_32b uv = v.normalized();

  float dt = uv.dot(n);
  float discriminant = 1.0f - niOverNt * niOverNt * (1 - dt * dt);

  if (discriminant > 0)
  {
    refracted = niOverNt * (uv - n * dt) - n * sqrt(discriminant);

    return true;
  }
  else
    return false;
}

bool Lambertian::scatter(const Ray& r, const HitRecord& rec, Vec3_32b& attentuation, Ray& scattered) const
{
  Vec3_32b target = rec.point + rec.normal + randomPointInUnitSphere();

  scattered = Ray(rec.point, target - rec.point);
  attentuation = albedo;

  return true;
}

bool Metal::scatter(const Ray & r, const HitRecord & rec, Vec3_32b & attentuation, Ray & scattered) const
{
  Vec3_32b reflected = reflect(r.D.normalized(), rec.normal);

  scattered = Ray(rec.point, reflected + fuzz * randomPointInUnitSphere());
  attentuation = albedo;

  return (scattered.D.dot(rec.normal) > 0);
}

bool Dielectrict::scatter(const Ray & r, const HitRecord & rec, Vec3_32b & attentuation, Ray & scattered) const
{
  Vec3_32b outward_normal;
  Vec3_32b reflected = reflect(r.D, rec.normal);
  float ni_over_nt;

  attentuation = Vec3_32b(1.0, 1.0, 1.0);
  Vec3_32b refracted;

  float reflect_prob;
  float cosine;

  if (r.D.dot(rec.normal) > 0)
  {
    outward_normal = -rec.normal;
    ni_over_nt = ref_idx;
    cosine = ref_idx * r.D.dot(rec.normal) / r.D.length();
  }
  else
  {
    outward_normal = rec.normal;
    ni_over_nt = 1.0f / ref_idx;
    cosine = -r.D.dot(rec.normal) / r.D.length();
  }
  if (refract(r.D, outward_normal, ni_over_nt, refracted))
  {
    reflect_prob = schlick(cosine, ref_idx);
  }
  else
  {
    scattered = Ray(rec.point, reflected);
    reflect_prob = 1.0;
  }
  if (dice.roll() < reflect_prob)
  {
    scattered = Ray(rec.point, reflected);
  }
  else
  {
    scattered = Ray(rec.point, refracted);
  }

  return true;
}
