#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"

struct hit_record {
    Point3 p;
    Vec3 normal;
    double t;
};

class HitTable {
    public:
        virtual bool hit(const Ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};

#endif
