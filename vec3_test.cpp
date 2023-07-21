// Vec3 test code
#include <iostream>
#include "vec3.hpp"

int main() {
    Vec3 v1(1, 2, 3), v2(4, 5, 6);
    std::cout
        << v1 / 2 << '\n' // 0.5 1 1.5
        << 2 * v2 << '\n' // 8 10 12
        << v1 + v2 << '\n' // 5 7 9
        << dot(v1, v2) << '\n' // 32
        << cross(v1, v2) << '\n'; // -3 6 -3

    return 0;
}
