#include <zlib.h>

#include <iostream>
#include <png++/png.hpp>

void render() {
    std::cout << "hello world";

    png::image<png::rgb_pixel> image(720.f, 560.f);

    for (float y = 0; y < image.get_height(); ++y) {
        for (float x = 0; x < image.get_width(); ++x) {
            image[y][x] =
                png::rgb_pixel(x / image.get_width() * 255.f,
                               y / image.get_height() * 255.f, (x / y) * 255.f);
            // non-checking equivalent of image.set_pixel(x, y, ...);
        }
    }
    image.write("rgb.png");
}

int main() {
    render();
    return 0;
}