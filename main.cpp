// generate the ppm image content, output as plain text
#include <iostream>

#include "common.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "hittable_list.hpp"
#include "camera.hpp"

Color ray_color(const Ray &r, const HitTableList &world) {
    hit_record rec;
    // if the ray hits any object in the world
    if (world.hit(r, 0, infinity, rec)) {
        // normal vector
        Vec3 n = rec.normal;
        // x, y, z in the range (-1, 1)
        return 0.5 * Color(n.x()+1, n.y()+1, n.z()+1);
    }

    // background (the ray does not hit the sphere)
    Vec3 unit_direction = unit_vector(r.direction());
    // t in the range (0, 1), increases as y increases
    double t = 0.5 * (unit_direction.y() + 1.0);
    // interpolate wight (t=0) and sky blue (t=1)
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
    // image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;

    // world
    HitTableList world;
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // camera
    Camera camera;

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
                pixel_color += ray_color(r, world);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";

    return 0;
}
