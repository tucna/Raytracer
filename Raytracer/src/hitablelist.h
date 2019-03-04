#pragma once

#include "hitable.h"

class HitableList : public Hitable
{
public:
    HitableList() {}
    HitableList(Hitable **l, int n) { list = l; list_size = n; }

    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;

    Hitable **list;
    int list_size;
};

inline bool HitableList::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool hitAnything = false;
    float closest_so_far = t_max;

    for (int i = 0; i < list_size; i++)
    {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
        {
            hitAnything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hitAnything;
}
