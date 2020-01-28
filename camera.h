#ifndef _CAMERA_H_
#define _CAMERA_H_

#include<cmath>
#include<iostream>
#include "geometry.h"
#include "sphere.h"
#include "light.h"
#include "material.h"

class Camera {
    public: Camera() {}

    public:
        bool scene_intersect(const Vec3f orig, const Vec3f dir, std::vector<Sphere> spheres, Vec3f &hit, Vec3f &N, Material &material, float limit) {
            float sphere_dist = std::numeric_limits<float>::max();
            for (size_t i = 0; i < spheres.size(); i++) {
                float ray_dist = std::numeric_limits<float>::max();
                if (spheres[i].ray_intersect(orig, dir, ray_dist) && ray_dist < sphere_dist) {
                    sphere_dist = ray_dist;
                    hit = orig + dir * sphere_dist;
                    N = (hit - spheres[i].center).normalize();
                    material = spheres[i].material;
                }
            }

            return sphere_dist <= limit ? true : false;
        }

        Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, std::vector<Sphere> &spheres, std::vector<Light> lights) {
            const float limit = 1000;

            Vec3f N, hit;
            Material material;

            if (!scene_intersect(orig, dir, spheres, hit, N, material, limit)) {
                return Vec3f(0.4, 0.5, 0.6);
            }

            int intensity = 0;
            for (size_t i = 0; i < lights.size(); i++) {
                Vec3f light_dir = (lights[i].position - hit).normalize();
                intensity += lights[i].intensity * std::max(0.f, N * light_dir);
            }

            return material.diffuse_color * intensity;
        }
    
};

#endif