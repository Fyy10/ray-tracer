#ifndef MATERIAL_H
#define MATERIAL_H

#include "common.hpp"

struct hit_record;

class Material {
    public:
        virtual bool scatter(
            const Ray &r_in, const hit_record &rec, Color &attenuation, Ray &scattered
        ) const = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(const Color &a) : albedo(a) {}

        virtual bool scatter(
            const Ray &r_in, const hit_record &rec, Color &attenuation, Ray &scattered
        ) const override {
            // Vec3 scatter_dir = rec.normal + random_in_unit_sphere();
            Vec3 scatter_dir = rec.normal + random_unit_vector();
            // Vec3 scatter_dir = random_in_hemisphere(rec.normal);

            // if the scatter direction is zero vector, set it to surface normal
            if (scatter_dir.near_zero()) {
                scatter_dir = rec.normal;
            }

            scattered = Ray(rec.p, scatter_dir);
            attenuation = albedo;
            return true;
        }

    public:
        Color albedo;
};

class Metal : public Material {
    public:
        Metal(const Color &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
            const Ray &r_in, const hit_record &rec, Color &attenuation, Ray &scattered
        ) const override {
            Vec3 reflected_dir = reflect(r_in.direction(), unit_vector(rec.normal));
            scattered = Ray(rec.p, reflected_dir + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0.0);
        }

    public:
        Color albedo;
        double fuzz;
};

class Dielectric : public Material {
    public:
        Dielectric(const Color &a, double n) : albedo(a), ri(n) {}
        Dielectric(double n) : ri(n) {
            // white
            albedo = Color(1, 1, 1);
        }

        virtual bool scatter(
            const Ray &r_in, const hit_record &rec, Color &attenuation, Ray &scattered
        ) const override {
            attenuation = albedo;
            double ratio = rec.front_face ? (1.0/ri) : ri;

            Vec3 unit_r_in = unit_vector(r_in.direction());
            Vec3 refracted_dir = refract(unit_r_in, rec.normal, ratio);

            scattered = Ray(rec.p, refracted_dir);
            return true;
        }

    public:
        Color albedo;
        // refractive index
        double ri;
};

#endif
