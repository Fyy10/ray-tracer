#ifndef COLOR_H
#define COLOR_H

#include "vec3.hpp"
#include <iostream>

void write_color(std::ostream &out, Color pixel_color, int samples_per_pixel=1) {
    Color copied_pixel_color = Color(pixel_color);

    // divide the color by the number of samples
    copied_pixel_color /= double(samples_per_pixel);
    double r = sqrt(copied_pixel_color.x());
    double g = sqrt(copied_pixel_color.y());
    double b = sqrt(copied_pixel_color.z());

    // write the translated [0, 255] value of each color component
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
