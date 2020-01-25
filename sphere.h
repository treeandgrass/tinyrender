#ifndef _SPHERE_H_
#define _SPHERE_H_
#include<cmath>
#include<iostream>
#include "geometry.h"

struct Sphere {
    Vec3f center;
    float radius;

    Sphere(const Vec3f &c, const float &r): center(c), radius(r) {}

    bool ray_intersect(const Vec3f &orig, const Vec3f &dir, float &t0) const {
        Vec3f L = center - orig;
        float tca = L * dir;
        float D = L * L - tca * tca;
        if (D > radius * radius) return false;

        float pi = sqrtf(radius * radius - D);
        t0 = tca - pi;
        float t1 = tca + pi;
        if (t0 < 0) t0 = t1;
        if (t0 < 0) return false;
        return true;
    }
};

#endif