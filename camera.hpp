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
        // aperture: the diameter of the camera lens
        // focus_distance: the distance between the camera and the focus plane
        Camera(
            Point3 look_from,
            Point3 look_at,
            Vec3 vup,
            double vfov,
            double aspect_ratio,
            double aperture,
            double focus_distance
        ) {
            double theta = degrees_to_radians(vfov);
            double h = tan(theta/2);

            double viewport_height = 2.0 * h;
            double viewport_width = aspect_ratio * viewport_height;

            // (u, v, w) are base vectors
            // focal_length is 1, so unit vector here
            w = unit_vector(look_from - look_at);
            // we want unit vector for all base vectors
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin = look_from;
            horizontal = focus_distance * viewport_width * u;
            vertical = focus_distance * viewport_height * v;
            upper_left_corner = origin - horizontal/2 + vertical/2 - focus_distance*w;

            lens_radius = aperture / 2;
        }

        Ray get_ray(double s, double t) const {
            Vec3 rand_vec = lens_radius * random_in_unit_disk();
            Vec3 offset = rand_vec.x() * u + rand_vec.y() * v;
            Point3 ray_origin = origin + offset;
            return Ray(
                ray_origin,
                upper_left_corner + s*horizontal - t*vertical - ray_origin
            );
        }

    private:
        Point3 origin;
        Point3 upper_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 u, v, w;
        double lens_radius;
};

#endif
