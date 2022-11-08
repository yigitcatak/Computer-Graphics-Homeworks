#include "Utility.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <glm/geometric.hpp>
#include "Camera.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Material.hpp"

glm::vec3 ray_color(const Ray &ray, const std::vector<std::shared_ptr<Hittable>> &objects, int depth)
{
    if (depth == 0)
        return glm::vec3(0);

    hitRecord closestRecord;
    if (getClosestHittable(ray, objects, closestRecord, 0.001))
    {
        glm::vec3 color = closestRecord.material_ptr->getColor();
        Ray reflectedRay = closestRecord.material_ptr->getReflection(ray.getDir(), closestRecord.surface_normal, closestRecord.P);
        return color * ray_color(reflectedRay,objects,depth-1);
    }

    glm::vec3 dir = ray.getDir();
    float y = glm::normalize(dir).y;
    float t = (y + 1) * 0.5;
    return (1.0f - t) * glm::vec3(1) + t * glm::vec3(0.5, 0.7, 1.0);
}

int main(int argc, char const *argv[])
{
    // Image
    const float aspect_ratio = 16.0 / 9.0;
    const int image_width = 800, image_height = image_width / aspect_ratio;
    std::ofstream image_file("output.ppm");
    const int sample_size = 50; // for antialiasing
    const int max_depth = 100;  // for shadows

    image_file << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    glm::vec3 camera_origin(0, 0, 0);
    float wpWidth = 2, wpHeight = wpWidth / aspect_ratio, focalLen = 1;

    Camera camera(camera_origin, wpWidth, wpHeight, focalLen, aspect_ratio);

    // Materials
    auto pink = std::make_shared<Lambertian>(glm::vec3(0.7, 0.3, 0.3));
    auto green = std::make_shared<Lambertian>(glm::vec3(0.8, 0.8, 0.0));
    auto metal = std::make_shared<Metal>(glm::vec3(0.5, 0.5, 0.5));

    // World
    std::vector<std::shared_ptr<Hittable>> objects;

    Sphere sphere(glm::vec3(0, 0, -2), 0.5, pink);
    Sphere sphere2(glm::vec3(0.5, 0, -1.5), 0.5, metal);
    Sphere ground(glm::vec3(0, -100.5, -1), 100, green);
    objects.push_back(std::make_shared<Sphere>(ground));
    objects.push_back(std::make_shared<Sphere>(sphere));
    objects.push_back(std::make_shared<Sphere>(sphere2));
    
    // Render
    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rPicture Progress: " << (int)(((image_height - j) / (float)image_height) * 100) << '%' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            glm::vec3 pixel_color(0);
            for (int s = 0; s < sample_size; s++)
            {
                auto scaling = 1.0 / sample_size;
                float u = ((i + randomDouble()) / (image_width - 1.0)) * wpWidth;
                float v = ((j + randomDouble()) / (image_height - 1.0)) * wpHeight;
                Ray ray = camera.getRay(u, v);
                glm::vec3 color = ray_color(ray, objects, max_depth);
                pixel_color += color;
            }
            writeImage((1.0 / sample_size) * pixel_color, image_file);
        }
    }
    image_file.close();
    return 0;
}