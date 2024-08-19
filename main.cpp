#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor WHITE(255, 255, 255, 255);

Model *model = nullptr;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
TGAColor scaleColorIntensity(const TGAColor& color, float intensity) {
    return TGAColor(
        std::min(255, static_cast<int>(color.r * intensity)),
        std::min(255, static_cast<int>(color.g * intensity)),
        std::min(255, static_cast<int>(color.b * intensity)),
        color.a  // Assuming a is the alpha component
    );
}

Vec3f computeBarycentric2D(float x, float y, const Vec3f* pts) {
    Vec3f v0 = pts[2] - pts[0], v1 = pts[1] - pts[0], v2 = Vec3f(x, y, 0.0f) - pts[0];
    float d00 = v0 * v0;
    float d01 = v0 * v1;
    float d11 = v1 * v1;
    float d20 = v2 * v0;
    float d21 = v2 * v1;
    float denom = d00 * d11 - d01 * d01;
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;
    return {u, v, w};
}

void rasterizeTriangle(const Vec3f* pts, const Vec3f* world_pts, float* zbuffer, TGAImage &image) {
    Vec2f bboxmin( std::numeric_limits<float>::max(),  std::numeric_limits<float>::max());
    Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
    Vec2f clamp(image.get_width() - 1, image.get_height() - 1);

    for (int i = 0; i < 3; i++) {
        bboxmin.x = std::max(0.0f, std::min(bboxmin.x, pts[i].x));
        bboxmin.y = std::max(0.0f, std::min(bboxmin.y, pts[i].y));

        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
    }

    Vec3f P;
    for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
        for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
            Vec3f bc_screen = computeBarycentric2D(P.x, P.y, pts);
            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
            P.z = 0;
			for (int i = 0; i < 3; i++) {
				if (i == 0) P.z += pts[i].z * bc_screen.x;
				if (i == 1) P.z += pts[i].z * bc_screen.y;
				if (i == 2) P.z += pts[i].z * bc_screen.z;
}
            int idx = int(P.x + P.y * SCREEN_WIDTH);
            if (zbuffer[idx] < P.z) {
                zbuffer[idx] = P.z;
                float intensity = (world_pts[0] - world_pts[1]).norm() * bc_screen.y + (world_pts[1] - world_pts[2]).norm() * bc_screen.z + (world_pts[2] - world_pts[0]).norm() * bc_screen.x;
				image.set(P.x, P.y, scaleColorIntensity(WHITE, intensity));
            }
        }
    }
}

Vec3f projectVertexToScreen(const Vec3f& vertex) {
    return Vec3f(int((vertex.x + 1.0) * SCREEN_WIDTH / 2.0 + 0.5), int((vertex.y + 1.0) * SCREEN_HEIGHT / 2.0 + 0.5), vertex.z);
}

void renderModel(TGAImage &image) {
    float *zbuffer = new float[SCREEN_WIDTH * SCREEN_HEIGHT];
    std::fill(zbuffer, zbuffer + SCREEN_WIDTH * SCREEN_HEIGHT, -std::numeric_limits<float>::max());

    for (int i = 0; i < model->nfaces(); i++) {
        Vec3f screen_coords[3], world_coords[3];
        for (int j = 0; j < 3; j++) {
            world_coords[j] = model->vert(model->face(i)[j]);
            screen_coords[j] = projectVertexToScreen(world_coords[j]);
        }
        rasterizeTriangle(screen_coords, world_coords, zbuffer, image);
    }

    delete[] zbuffer;
}

int main(int argc, char** argv) {
    model = argc == 2 ? new Model(argv[1]) : new Model("obj/african_head.obj");
    TGAImage image(SCREEN_WIDTH, SCREEN_HEIGHT, TGAImage::RGB);

    renderModel(image);

    image.flip_vertically(); // Set the origin to the bottom-left corner
    image.write_tga_file("/output/african_head.tga");
    delete model;
    return 0;
}