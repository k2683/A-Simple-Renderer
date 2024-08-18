#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include <memory>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;
const int width  = 800;
const int height = 800;

// Bresenham's Line Algorithm
void lineBresenham(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color) {
    int dx = std::abs(x2 - x1);
    int dy = -std::abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        image.set(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            if (x1 == x2) break;
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            if (y1 == y2) break;
            err += dx;
            y1 += sy;
        }
    }
}
std::pair<int, int> modelToScreen(const Vec3f& v, int width, int height) {
    return {
        static_cast<int>((v.x + 1.0) * width / 2.0),
        static_cast<int>((v.y + 1.0) * height / 2.0)
    };
}

void drawObj() {
    std::unique_ptr<Model> model(new Model("obj/african_head.obj"));
    TGAImage image(width, height, TGAImage::RGB);
    
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        
        for (int j = 0; j < 3; j++) {
            auto [x0, y0] = modelToScreen(model->vert(face[j]), width, height);
            auto [x1, y1] = modelToScreen(model->vert(face[(j + 1) % 3]), width, height);
            lineBresenham(x0, y0, x1, y1, image, white);
        }
    }

    image.flip_vertically(); // flips the image vertically
    image.write_tga_file("output/african_head.tga"); // writes to file
}


int main(int argc, char** argv) {
    drawObj();

    return 0;
}
