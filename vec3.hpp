#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3 {
    public:
        Vec3() : e{0, 0, 0} {}
        Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
        Vec3(const Vec3 &v) : e{v.e[0], v.e[1], v.e[2]} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        Vec3& operator+=(const Vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vec3& operator/=(const double t) {
            *this *= 1/t;
            return *this;
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double length() const {
            return sqrt(length_squared());
        }

    public:
        double e[3];
};

// type aliases for Vec3
using Point3 = Vec3; // 3D point
using Color = Vec3; // RGB color

// Vec3 utility functions
inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]);
}

// element-wise product
inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
}

// scaling mult
inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

// scaling mult
inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

// scaling div
inline Vec3 operator/(const Vec3 &v, double t) {
    return (1/t) * v;
}

// dot product
inline double dot(const Vec3 &u, const Vec3 &v) {
    Vec3 vec_mult = u * v;
    return vec_mult[0] + vec_mult[1] + vec_mult[2];
}

// cross product
inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(
        u[1]*v[2] - u[2]*v[1],
        u[2]*v[0] - u[0]*v[2],
        u[0]*v[1] - u[1]*v[0]
    );
}

inline Vec3 unit_vector(const Vec3 &v) {
    return v / v.length();
}

#endif
