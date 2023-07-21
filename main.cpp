// generate the ppm image content, output as plain text
#include <iostream>
#include "vec3.hpp"
#include "color.hpp"

int main() {
    // image size
    const int image_width = 256;
    const int image_height = 256;

    // header
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // content
    for (int i = 0; i < image_height; i++) {
        std::cerr << "\rScan lines remaining: " << image_height - i - 1 << ' ' << std::flush;
        for (int j = 0; j < image_width; j++) {
            Color pixel_color(double(i)/(image_height-1), double(j)/(image_width-1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";

    return 0;
}
