#ifndef _CAMERA_H_
#define _CAMERA_H_

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
        Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, std::vector<Sphere> &spheres) {
            float sphere_dist = std::numeric_limits<float>::max();
            size_t hit_index = -1;
            
            for (size_t i = 0; i < spheres.size(); i++) {
                float s_dist = std::numeric_limits<float>::max();
                if (spheres[i].ray_intersect(orig, dir, s_dist) && s_dist < sphere_dist) {
                    sphere_dist = s_dist;
                    hit_index = i;
                }
            }

            if (hit_index < 0) {
                return Vec3f(0.2, 0.7, 0.8);
            }
            std::cout << hit_index << std::endl;

            Vec3f hit = orig + dir * sphere_dist;
            const Vec3f N = (hit - spheres[hit_index].center).normalize();
            // color
            const Vec3f material_color(0.3, 0.4, 0.5);
            int intensity = 0;


            for (size_t i = 0; i < lights.size(); i++) {
                Light light = lights[i];
                Vec3f light_dir = (hit - light.position).normalize();
                intensity += light.itensity * std::max(0.f, light_dir * N);
            }

            return material_color * intensity;
        }
    
};

#endif