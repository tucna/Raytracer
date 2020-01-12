#pragma once

#include <vector>

#include "hitable.h"

class HitableList : public Hitable
{
public:
  HitableList() {}
  HitableList(std::vector<Hitable*>& list) { _list = list; }

  virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const;

private:
  std::vector<Hitable*> _list;
};

inline bool HitableList::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const
{
  HitRecord tempRec;
  bool hitAnything = false;
  float closestSoFar = tMax;

  for (int i = 0; i < _list.size(); i++)
  {
    if (_list[i]->hit(r, tMin, closestSoFar, tempRec))
    {
      hitAnything = true;
      closestSoFar = tempRec.t;
      rec = tempRec;
    }
  }

  return hitAnything;
}
