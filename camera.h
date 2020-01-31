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

            float checkerboard_dist = std::numeric_limits<float>::max();
            if (dir.y < -1e-3) {
                float d = -(4 + orig.y) / dir.y;
                Vec3f pt = orig + dir * d;
                if (d > 0 && fabs(pt.x) < 10 && pt.z < -10 && pt.z > -30 && d < sphere_dist) {
                    hit = pt;
                    N = Vec3f(0, 1, 0);
                    checkerboard_dist = d;

                    material.diffuse_color = (int(0.5 * hit.x) + int(0.5 * pt.z)) & 1 ? Vec3f(1, 1, 1) : Vec3f(1, .7, .3);
                    material.diffuse_color = material.diffuse_color * 0.3;
                }
            }
            return std::min(sphere_dist, checkerboard_dist) < limit;
        }

        Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, std::vector<Sphere> &spheres, std::vector<Light> lights, size_t depth) {
            const float limit = 1000;

            Vec3f N, hit;
            Material material;

            if (depth > 4 || !scene_intersect(orig, dir, spheres, hit, N, material, limit)) {
                return Vec3f(0.4, 0.5, 0.6);
            }

            Vec3f reflect_dir = reflect(dir, N);
            Vec3f refract_dir = refract(dir, N, material.refractive_index);

            Vec3f reflect_orig = N * reflect_dir < 0 ? hit - N * 1e-3 : hit + N * 1e-3;
            Vec3f refract_orig = N * refract_dir < 0 ? hit - N * 1e-3 : hit + N * 1e-3;

            Vec3f reflect_color = cast_ray(reflect_orig, reflect_dir, spheres, lights, depth + 1);
            Vec3f refract_color = cast_ray(refract_orig, refract_dir, spheres, lights, depth);

            float diffuse_light_intensity = 0, specular_light_intensity = 0;
            for (size_t i = 0; i < lights.size(); i++) {
                Vec3f shadow_N, shadow_hit;
                Material shadow_material;
                Vec3f light_dir = (lights[i].position - hit).normalize();
                float light_distance = (lights[i].position - hit).norm();
                Vec3f shadow_orig = N * light_dir < 0 ? hit - N * 1e-3 : hit + N * 1e-3;

                if (scene_intersect(shadow_orig, light_dir, spheres, shadow_hit, shadow_N, shadow_material, limit) && (shadow_hit - shadow_orig).norm() < light_distance )
                    continue;

                diffuse_light_intensity += lights[i].intensity * std::max(0.f, N * light_dir);
                specular_light_intensity += lights[i].intensity * powf(std::max(0.f, reflect(light_dir, N) * dir),  material.specular_exponent);
            }

            return material.diffuse_color * diffuse_light_intensity * material.albedo[0] + Vec3f(1., 1., 1.) * specular_light_intensity * material.albedo[1] + reflect_color * material.albedo[2] + refract_color * material.albedo[3];
        }
    
};

#endif