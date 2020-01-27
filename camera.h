#ifndef __CAMERA_H__
#define __CAMERA_H_

#include<cmath>
#include<iostream>
#include "geometry.h"
#include "sphere.h"
#include "light.h"

class Camera {
    public: Camera(std::vector<Light> &lights): lights(lights) {}
    public:
        std::vector<Light> lights;

    public:
        Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, const Sphere &sphere) {
            float sphere_dist = std::numeric_limits<float>::max();
            if (!sphere.ray_intersect(orig, dir, sphere_dist)) {
                return Vec3f(0.2, 0.7, 0.8);
            }
            return Vec3f(0.4, 0.4, 0.3);
        }

    
};

#endif