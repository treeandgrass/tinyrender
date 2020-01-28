#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "geometry.h"

struct Material {
    Material(const Vec3f &color): diffuse_color(color) {}
    Material(): diffuse_color() {}
    
    Vec3f diffuse_color;
};

#endif