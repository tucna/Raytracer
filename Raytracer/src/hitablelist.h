#pragma once

#include "hitable.h"

template <typename T>
class HitableList : public Hitable<T>
{
public:
    HitableList() {}
    HitableList(Hitable<T> **l, int n) { list = l; list_size = n; }

    virtual bool hit(const Ray<T>& r, float t_min, float t_max, HitRecord<T>& rec) const;

    Hitable<T> **list;
    int list_size;
};

template<typename T>
inline bool HitableList<T>::hit(const Ray<T>& r, float t_min, float t_max, HitRecord<T>& rec) const
{
    HitRecord<T> temp_rec;
    bool hitAnything = false;
    double closest_so_far = t_max;

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
