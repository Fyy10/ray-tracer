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

        // return true if the vector is close to zero in all dimensions
        bool near_zero() const {
            double eps = 1e-8;
            return (fabs(e[0]) < eps) && (fabs(e[1]) < eps) && (fabs(e[2]) < eps);
        }

        // generate a random vector with 3 components in the range [0, 1)
        inline static Vec3 random() {
            return Vec3(rand_double(), rand_double(), rand_double());
        }

        // generate a random vector with 3 components in the range [min, max)
        inline static Vec3 random(double min, double max) {
            return Vec3(rand_double(min, max), rand_double(min, max), rand_double(min, max));
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

Vec3 random_in_unit_sphere() {
    while (true) {
        Vec3 p = Vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

Vec3 random_in_hemisphere(const Vec3 &normal) {
    Vec3 p = random_in_unit_sphere();
    if (dot(p, normal) > 0.0) {
        return p;
    } else {
        return -p;
    }
}

// compute the reflect vector according to the incident ray and surface normal
Vec3 reflect(const Vec3 &v, const Vec3 &n) {
    return v - 2*dot(v, n)*n;
}

// compute the refract vector according to the incident ray and surface normal
// return the reflect vector if total reflection happens
Vec3 refract(const Vec3 &v, const Vec3 &n, double n1_over_n2) {
    double cos_theta = fmin(dot(-v, n), 1.0);
    double sin_theta = sqrt(fabs(1 - cos_theta * cos_theta));

    if (sin_theta * n1_over_n2 > 1.0) {
        // total reflection
        return reflect(v, n);
    }

    // regular refraction
    Vec3 r_perp = n1_over_n2 * (v + cos_theta * n);
    Vec3 r_par = -sqrt(fabs(1 - r_perp.length_squared())) * n;
    return r_perp + r_par;
}

#endif
