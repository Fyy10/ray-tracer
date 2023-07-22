// generate the ppm image content, output as plain text
#include <iostream>
#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"

// check if the ray hits the sphere
bool hit_sphere(const Point3 &center, double radius, const Ray &r) {
    Vec3 A_C = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(r.direction(), A_C);
    double c = dot(A_C, A_C) - radius * radius;
    double delta = b*b - 4*a*c;
    return delta > 0;
}

Color ray_color(const Ray &r) {
    // draw blue if the ray hits the sphere
    if (hit_sphere(Point3(0, 0, -1), 0.5, r)) { return Color(0, 0, 1); }

    Vec3 unit_direction = unit_vector(r.direction());
    // t in the range (0, 1), increases as y increases
    double t = 0.5 * (unit_direction.y() + 1.0);
    // interpolate wight (t=0) and sky blue (t=1)
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
    // image size
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // camera
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    Point3 origin = Point3(0.0, 0.0, 0.0);
    Vec3 horizontal = Vec3(viewport_width, 0, 0);
    Vec3 vertical = Vec3(0, viewport_height, 0);
    Point3 upper_left_corner = origin - horizontal / 2 + vertical / 2 - Vec3(0, 0, focal_length);

    // ppm header
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // content
    // scan from the upper left corner to the lower right corner, line by line
    for (int i = 0; i < image_height; i++) {
        std::cerr << "\rScan lines remaining: " << image_height - i - 1 << ' ' << std::flush;
        for (int j = 0; j < image_width; j++) {
            double u = double(j) / (image_width - 1);
            double v = double(i) / (image_height - 1);
            Ray r(origin, upper_left_corner + u*horizontal - v*vertical);
            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";

    return 0;
}
