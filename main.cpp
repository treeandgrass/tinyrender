
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
    Material      ivory(Vec3f(0.4, 0.4, 0.3),   Vec2f(0.6,  0.3),  50.);
    Material red_rubber(Vec3f(0.3, 0.1, 0.1),   Vec2f(0.9,  0.1),  10.);

    std::vector<Light> lights;
    // lights
    lights.push_back(Light(Vec3f(-20, 20,  20), 1.5));
    lights.push_back(Light(Vec3f( 30, 50, -25), 1.8));
    lights.push_back(Light(Vec3f( 30, 20,  30), 1.7));

    // camera
    Camera camera;

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vec3f(-3,    0,   -16), 2,      ivory));
    spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2,      red_rubber));
    spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
    spheres.push_back(Sphere(Vec3f( 7,    5,   -18), 4,     ivory));
    // run
    render(spheres, M_PI / 2 , camera, lights);

    return 0;
}