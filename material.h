#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "geometry.h"

struct Material {
    // Material(): diffuse_color() {}
    Material(const Vec3f color): diffuse_color(color) {}
    Material(): diffuse_color(), albedo(1, 0), specular_exponent() {}
    Material(const Vec3f &color, Vec2f albedo, float specular_exponent): diffuse_color(color), albedo(albedo), specular_exponent(specular_exponent) {}
    
    Vec3f diffuse_color;
    Vec2f albedo;
    float specular_exponent;
};

#endif