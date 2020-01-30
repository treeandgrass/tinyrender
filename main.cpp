
#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<limits>
#include "geometry.h"
#include "sphere.h"
#include "camera.h"
#include "light.h"
#include "material.h"
#include "engine.h"


int main() {
    // material
    // Material      ivory(Vec3f(0.4, 0.4, 0.3),   Vec3f(0.6,  0.3, 0.1), 50.);
    // Material red_rubber(Vec3f(0.3, 0.1, 0.1),   Vec3f(0.9,  0.1, 0.0), 10.);
    // Material     mirror(Vec3f(1.0, 1.0, 1.0),   Vec3f(0.0, 10.0, 0.8), 1425.);
    Material      ivory(Vec3f(0.4, 0.4, 0.3),  Vec4f(0.6,  0.3, 0.1, 0.0), 1.0, 50.);
    Material      glass(Vec3f(0.6, 0.7, 0.8),  Vec4f(0.0,  0.5, 0.1, 0.8), 1.5, 125.);
    Material red_rubber(Vec3f(0.3, 0.1, 0.1),  Vec4f(0.9,  0.1, 0.0, 0.0), 1.0, 10.);
    Material     mirror(Vec3f(1.0, 1.0, 1.0),  Vec4f(0.0, 10.0, 0.8, 0.0), 1.0, 1425.);

    std::vector<Light> lights;
    // lights
    lights.push_back(Light(Vec3f(-20, 20,  20), 1.5));
    lights.push_back(Light(Vec3f( 30, 50, -25), 1.8));
    lights.push_back(Light(Vec3f( 30, 20,  30), 1.7));

    // camera
    Camera camera;

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vec3f(-3,    0,   -16), 2,      ivory));
    spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2,      glass));
    spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
    spheres.push_back(Sphere(Vec3f( 7,    5,   -18), 4,     mirror));
    // run
    render(spheres, M_PI / 2 , camera, lights);

    return 0;
}