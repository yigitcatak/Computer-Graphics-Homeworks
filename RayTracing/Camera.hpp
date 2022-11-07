#pragma once
#include <glm/vec3.hpp>
#include "Ray.hpp"

class Camera
{
private:
    float aspect_ratio;
    float viewport_width;
    float viewport_height;
    float focal_length;
    glm::vec3 origin;

public:
    Camera();
    Camera(glm::vec3 origin, float wpWidth, float wpHeight, float focalLen, float aspRatio):
    origin(origin), viewport_width(wpWidth), viewport_height(wpHeight), focal_length(focalLen), aspect_ratio(aspRatio) {}
    ~Camera() {}
    int getviewportWidth() { return viewport_width; }
    int getviewportHeight() { return viewport_height; }
    Ray getRay(float u, float v);
};

Ray Camera::getRay(float u, float v)
{
    auto lower_left_corner = glm::vec3(0, 0, -focal_length) + glm::vec3(-viewport_width / 2, 0, 0) + glm::vec3(0, -viewport_height / 2, 0);
    return Ray(origin, lower_left_corner + glm::vec3(u,0,0) + glm::vec3(0,v,0));
}
