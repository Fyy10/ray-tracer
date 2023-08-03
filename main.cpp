// generate the ppm image content, output as plain text
#include <iostream>

#include "common.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "hittable_list.hpp"
#include "camera.hpp"
#include "material.hpp"

Color ray_color(const Ray &r, const HitTableList &world, int remaining_depth) {
    hit_record rec;
    // if there is no remaining depth, no more light is gathered
    // Color(0, 0, 0) is black
    if (remaining_depth <= 0) {
        return Color(0, 0, 0);
    }

    // if the ray hits any object in the world
    if (world.hit(r, 0.0001, infinity, rec)) {
        // // generate reflection (scattered) rays
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, remaining_depth-1);
        } else {
            // black
            return Color(0, 0, 0);
        }
    }

    // background (the ray does not hit the sphere)
    Vec3 unit_direction = unit_vector(r.direction());
    // t in the range (0, 1), increases as y increases
    double t = 0.5 * (unit_direction.y() + 1.0);
    // interpolate white (t=0) and sky blue (t=1)
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

HitTableList random_scene() {
    HitTableList world;

    shared_ptr<Material> ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double material_selector = rand_double();
            Point3 center(a + 0.9*rand_double(), 0.2, b + 0.9*rand_double());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                // set the material ptr
                if (material_selector < 0.8) {
                    // diffuse material
                    Color albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                } else if (material_selector < 0.95) {
                    // metal
                    Color albedo = Color::random(0.5, 1);
                    double fuzz = rand_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                } else {
                    // dielectric
                    sphere_material = make_shared<Dielectric>(1.5);
                }

                // add to scene
                world.add(make_shared<Sphere>(center, 0.2, sphere_material));
            }
        }
    }

    shared_ptr<Material> material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    shared_ptr<Material> material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    shared_ptr<Material> material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

int main() {
    // image
    const double aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;
    const int max_reflection_depth = 50;

    // world
    HitTableList world = random_scene();

    // camera
    Point3 look_from(13, 2, 3);
    Point3 look_at(0, 0, 0);
    Vec3 vup(0, 1, 0);
    double aperture = 0.1;
    double focus_dist = 10;
    Camera camera(look_from, look_at, vup, 20.0, aspect_ratio, aperture, focus_dist);

    // ppm header
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // content
    // scan from the upper left corner to the lower right corner, line by line
    for (int i = 0; i < image_height; i++) {
        std::cerr << "\rScan lines remaining: " << image_height - i - 1 << ' ' << std::flush;
        for (int j = 0; j < image_width; j++) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                double u = (j + rand_double()) / (image_width - 1);
                double v = (i + rand_double()) / (image_height - 1);
                Ray r = camera.get_ray(u, v);
                pixel_color += ray_color(r, world, max_reflection_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";

    return 0;
}
