
#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<limits>
#include "geometry.h"
#include "sphere.h"
#include "camera.h"
#include "light.h"


void render(std::vector<Sphere> & spheres, float fov, Camera &camera) {
    const int width = 1024;
    const int height = 768;

    std::vector<Vec3f> framebuffer(width * height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float x = (2 * (j + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
            float y = -(2 * (i + 0.5) / (float)height - 1) * tan(fov / 2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[j + i * width] = camera.cast_ray(Vec3f(0., 0., 0.), dir, spheres);
        }
    }

    std::ofstream ofs;
    ofs.open("./out.ppm");

    ofs << "P6\n" << width << " " << height << "\n255\n";
    size_t len = width * height;
    for (size_t i = 0; i < len; i++ ) {
        for (size_t j = 0; j < 3; j++) {
            ofs << (char) (255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}



int main() {
    
    int light_size = 4;
    float fov = 80;

    std::vector<Light> lights;
    for (size_t i = 0; i < light_size; i++) {
        lights.push_back(Light(Vec3f(-i * 2, i * 4, 5 * i), 0.1 * i));
    }

    Camera camera(lights);

    std::vector<Sphere> spheres;
    int spehre_num = 4;
    for (size_t i = 0; i < spehre_num; i++) {
        spheres.push_back(Sphere(Vec3f(i * 6, i * 8, i * (-10)), i * 5));
    }

    render(spheres, fov, camera);
    return 0;
}