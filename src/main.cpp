#include <math.h>
#include <zlib.h>

#include <iostream>
#include <png++/png.hpp>

struct Vec3 {
    float x, y, z;
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    float dot(Vec3 vec3) const { return vec3.x * x + vec3.y * y + vec3.z * z; }
    Vec3 add(Vec3 vec3) const {
        return Vec3(x + vec3.x, y + vec3.y, z + vec3.z);
    }
    Vec3 minus(Vec3 vec3) const {
        return Vec3(x - vec3.x, y - vec3.y, z - vec3.z);
    }
    float length() const { return sqrtf(x * x + y * y + z * z); }
    Vec3 normalize() const {
        return Vec3(x / length(), y / length(), z / length());
    }
    Vec3 scale(float scalar) {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }
};

struct Ray {
    Vec3 origin;
    Vec3 direction;
    Ray(Vec3 o, Vec3 dir) : origin(o), direction(dir) {}
};
struct Sphere {
    Vec3 center;
    float radius;

    Sphere(const Vec3 &c, const float &rad) : center(c), radius(rad) {}

    bool ray_intersect(const Ray &ray, float &t0) const {
        Vec3 L = center.minus(ray.origin);
        float tca = ray.direction.dot(L);
        if (tca < 0) return false;
        float d2 = L.dot(L) - tca * tca;
        if (d2 > radius * radius) return false;
        float thc = sqrtf(radius * radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0) t0 = t1;
        if (t0 < 0) return false;
        return true;
    }
};

Vec3 cast_ray(const Ray &ray, const Sphere &sphere) {
    float intersection_distance = std::numeric_limits<float>::max();
    if (!sphere.ray_intersect(ray, intersection_distance)) {
        return Vec3(0.2, 0.7, 0.8).scale(255);
    }
    return Vec3(0.4, 0.4, 0.3).scale(255);
}

void render(const Sphere &sphere) {
    std::cout << "hello world";
    const float WIDTH = 1080;
    const float HEIGHT = 720;
    const float FOV = 90;

    png::image<png::rgb_pixel> screen(WIDTH, HEIGHT);

    for (float y = 0; y < screen.get_height(); ++y) {
        for (float x = 0; x < screen.get_width(); ++x) {
            float halfwidth = tan(FOV / 2);
            float ynorm = (2 * ((y + 0.5) / HEIGHT) - 1);  // between -1 and 1
            // adjusted for aspect ratio
            float xnorm = (2 * ((x + 0.5) / WIDTH) - 1) * (WIDTH / HEIGHT);

            float xworld = xnorm * halfwidth;
            float yworld = ynorm * halfwidth;

            Vec3 origin = Vec3(0, 0, 0);
            Vec3 dir = Vec3(xworld, yworld, -1).normalize();
            Ray ray = Ray(origin, dir);

            Vec3 rgb = cast_ray(ray, sphere);
            screen[y][x] = png::rgb_pixel(rgb.x, rgb.y, rgb.z);
            // non-checking equivalent of image.set_pixel(x, y, ...);
        }
    }
    screen.write("rgb.png");
}

int main() {
    Sphere sphere(Vec3(-2, -1, -10), 3);
    render(sphere);
    return 0;
}