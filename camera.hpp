#ifndef CAMERA_H
#define CAMERA_H

#include "common.hpp"

class Camera {
    public:
        // look_from: the origin of the camera
        // look_at: the point that the camera looks at
        // vup: the upward direction
        // vfov: vertical field of view in degrees
        // aspect_ratio: viewport_width / viewport_height
        Camera(
            Point3 look_from,
            Point3 look_at,
            Vec3 vup,
            double vfov,
            double aspect_ratio
        ) {
            double theta = degrees_to_radians(vfov);
            double h = tan(theta/2);

            double viewport_height = 2.0 * h;
            double viewport_width = aspect_ratio * viewport_height;

            // (u, v, w) are base vectors
            // focal_length is 1, so unit vector here
            Vec3 w = unit_vector(look_from - look_at);
            // we want unit vector for all base vectors
            Vec3 u = unit_vector(cross(vup, w));
            Vec3 v = cross(w, u);

            origin = look_from;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            upper_left_corner = origin - horizontal / 2 + vertical / 2 - w;
        }

        Ray get_ray(double u, double v) const {
            return Ray(origin, upper_left_corner + u*horizontal - v*vertical - origin);
        }

    private:
        Point3 origin;
        Point3 upper_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
};

#endif
