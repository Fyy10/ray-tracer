#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vec3.hpp"

class Sphere : public HitTable {
    public:
        Sphere() {}
        Sphere(Point3 c, double r, shared_ptr<Material> m) : center(c), radius(r), mat_ptr(m) {}

        virtual bool hit(const Ray &r, double t_min, double t_max, hit_record &rec) const override;

    public:
        Point3 center;
        double radius;
        shared_ptr<Material> mat_ptr;
};

bool Sphere::hit(const Ray &r, double t_min, double t_max, hit_record &rec) const {
    Vec3 A_C = r.origin() - center;
    double a = r.direction().length_squared();
    // h = b/2
    double h = dot(r.direction(), A_C);
    double c = A_C.length_squared() - radius * radius;
    double delta = h*h - a*c;

    if (delta < 0) return false;

    // find the nearest root that lies in the acceptable range
    double sqrtd = sqrt(delta);
    double root = (-h - sqrtd) / a;
    if (root < t_min || root > t_max) {
        root = (-h + sqrtd) / a;
        if (root < t_min || root > t_max) {
            return false;
        }
    }

    // a valid root found, set hit record
    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif
