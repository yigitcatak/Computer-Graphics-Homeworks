#pragma once
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <fstream>
#include <memory>
#include "Hittable.hpp"

void writeImage(glm::vec3 color, std::ofstream &output)
{
    int r = static_cast<int>(color.r == 1.0 ? 255 : color.r*256);
    int g = static_cast<int>(color.g == 1.0 ? 255 : color.g*256);
    int b = static_cast<int>(color.b == 1.0 ? 255 : color.b*256);

    output << r << " " << g << " " << b << std::endl;
}

bool getClosestHittable(const Ray &ray, const std::vector<std::shared_ptr<Hittable>> & objects, hitRecord& record, float threshold)
{
    bool hit = false;
    hitRecord temp_record;
    float closest_t = std::numeric_limits<float>::infinity();

    // for finding closest object to ray
    for (const auto &object : objects)
    {
        if (object->isHit(ray, threshold, temp_record))
        {
            hit = true;
            closest_t = temp_record.t;
            record = temp_record;
        }
    }
    return hit;
}

glm::vec3 operator*(float num, const glm::vec3 &rhs)
{
    return glm::vec3(rhs.x * num, rhs.y * num, rhs.z * num);
}

glm::vec3 operator*(const glm::vec3 &lhs, float num)
{
    return num*lhs;
}

glm::vec3 operator/(const glm::vec3 &lhs, float num)
{
    return (1/num)*lhs;
}

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec)
{
    os << vec.x << " " << vec.y << " " << vec.z << "\n";
}
