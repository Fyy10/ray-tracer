#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// using
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double rand_double() {
    // return a random real in [0, 1)
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    static std::mt19937 generator;
    return dist(generator);
}

inline double rand_double(double min, double max) {
    // return a random real in [min, max)
    return min + (max-min)*rand_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// common headers
#include "ray.hpp"
#include "vec3.hpp"

#endif
