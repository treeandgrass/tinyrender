#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "geometry.h"

struct Material {
    // Material(): diffuse_color() {}
    Material(const Vec3f color): diffuse_color(color) {}
    Material(): diffuse_color(), albedo(1, 0, 0, 0), specular_exponent(), refractive_index(1) {}
    Material(const Vec3f &color, Vec4f albedo, float refractive_index, float specular_exponent): diffuse_color(color), albedo(albedo), specular_exponent(specular_exponent), refractive_index(refractive_index) {}
    
    Vec3f diffuse_color;
    Vec4f albedo;
    float specular_exponent;
    float refractive_index;
};

#endif