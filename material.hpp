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
            Vec3 direction;

            // reflect according to the reflectance
            double cos_theta = fmin(dot(-unit_r_in, rec.normal), 1.0);
            if (reflectance(cos_theta, ratio) > rand_double()) {
                direction = reflect(unit_r_in, rec.normal);
            } else {
                direction = refract(unit_r_in, rec.normal, ratio);
            }

            scattered = Ray(rec.p, direction);
            return true;
        }

    public:
        Color albedo;
        // refractive index
        double ri;

    private:
        // Schlick's Approximation
        static double reflectance(double cos_theta, double n1_over_n2) {
            double r0 = (1-n1_over_n2) / (1+n1_over_n2);
            r0 = r0 * r0;
            return r0 + (1-r0) * pow(1-cos_theta, 5);
        }
};

#endif
