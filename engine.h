#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <fstream>
#include "sphere.h"
#include "camera.h"
#include "light.h"

void render(std::vector<Sphere> &spheres, float fov, Camera &camera, std::vector<Light> lights) {
    const int width = 1024;
    const int height = 768;

    std::vector<Vec3f> framebuffer(width * height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float x = (2 * (j + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
            float y = -(2 * (i + 0.5) / (float)height - 1) * tan(fov / 2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[j + i * width] = camera.cast_ray(Vec3f(0., 0., 0.), dir, spheres, lights, 1);
        }
    }

    std::ofstream ofs;
    ofs.open("./out.ppm");

    ofs << "P6\n" << width << " " << height << "\n255\n";
    size_t len = width * height;
    for (size_t i = 0; i < len; i++ ) {
        Vec3f &color = framebuffer[i];
        float max = std::max(color[0], std::max(color[1], color[2]));
        if (max > 1) color = color * (1 / max);
        for (size_t j = 0; j < 3; j++) {
            ofs << (char) (255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}

#endif