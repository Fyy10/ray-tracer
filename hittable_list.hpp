#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HitTableList : public HitTable {
    public:
        std::vector<shared_ptr<HitTable>> objects;

    public:
        HitTableList() {}
        HitTableList(shared_ptr<HitTable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<HitTable> object) { objects.push_back(object); }

        virtual bool hit(const Ray &r, double t_min, double t_max, hit_record &rec) const override;
};

bool HitTableList::hit(const Ray &r, double t_min, double t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_any = false;
    double closest_t = t_max;

    for (const shared_ptr<HitTable> &object : objects) {
        if (object->hit(r, t_min, closest_t, temp_rec)) {
            hit_any = true;
            closest_t = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_any;
}

#endif
