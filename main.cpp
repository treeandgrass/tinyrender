#include<iostream>
#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0,   255, 0,   255);
const int width  = 200;
const int height = 200;

void line(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(p0.x-p1.x)<std::abs(p0.y-p1.y)) {
        std::swap(p0.x, p0.y);
        std::swap(p1.x, p1.y);
        steep = true;
    }
    if (p0.x>p1.x) {
        std::swap(p0, p1);
    }

    for (int x=p0.x; x<=p1.x; x++) {
        float t = (x-p0.x)/(float)(p1.x-p0.x);
        int y = p0.y*(1.-t) + p1.y*t;
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}

Vec3f barycentric(Vec2i *pts, Vec2i p) {
    Vec3f u = cross_(Vec3f(pts[1].x - pts[0].x, pts[2].x - pts[0].x, pts[0].x - p.x), Vec3f(pts[1].y - pts[0].y, pts[2].y - pts[0].y, pts[0].y - p.y));
    if (std::abs(u.z) < 1) return Vec3f(-1, 1, 1);
    return Vec3f(1.0f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
}

Vec3f triangle(Vec2i * pts, TGAImage &image, TGAColor color) {
    Vec2i bboxmin(image.get_width() - 1, image.get_height() - 1);
    Vec2i bboxmax(0, 0);
    Vec2i clamp(image.get_width() - 1, image.get_height() - 1);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            if (j < 1) {
                bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
                bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
            } else {
                bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));
                bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
            }
        }
    }

    Vec2i P;
    for (P.x = bboxmin.x; P.x < bboxmax.x; P.x++) {
        for (P.y = bboxmin.y; P.y < bboxmax.y; P.y++) {
            Vec3f u = barycentric(pts, P);
            if (u.x < 0 || u.y < 0 || u.z < 0) continue;
            image.set(P.x, P.y, color);
        }
    }
}

// void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
//     line(t0, t1, image, color);
//     line(t1, t2, image, color);
//     line(t2, t0, image, color);
// }

int main(int argc, char** argv) {
    // TGAImage image(width, height, TGAImage::RGB);

    // Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)};
    // Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
    // Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};

    // triangle(t0[0], t0[1], t0[2], image, red);
    // triangle(t1[0], t1[1], t1[2], image, white);
    // triangle(t2[0], t2[1], t2[2], image, green);


    // image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    // image.write_tga_file("output.tga");
    // return 0;

    TGAImage frame(200, 200, TGAImage::RGB); 
    Vec2i pts[3] = {Vec2i(10,10), Vec2i(100, 30), Vec2i(190, 160)}; 
    triangle(pts, frame, TGAColor(235, 32, 212, 1)); 
    frame.flip_vertically(); // to place the origin in the bottom left corner of the image 
    frame.write_tga_file("framebuffer.tga");
    return 0; 
}
