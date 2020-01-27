#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "geometry.h"

struct Light {
    Light() {};
    Light(const Vec3f &p, const float i): position(p), itensity(i) {}
    Vec3f position;
    float itensity;
};

#endif