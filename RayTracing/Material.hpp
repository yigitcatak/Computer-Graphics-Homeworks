#pragma once
#include <glm/vec3.hpp>
#include "Ray.hpp"
#include "rand_utils.hpp"
class Material
{
private:
public:
    virtual glm::vec3 getReflection(const glm::vec3 &intersect_point, const glm::vec3 &surface_normal) const = 0;
    virtual glm::vec3 getColor() const = 0;
};

class Lambertian : public Material
{
private:
    glm::vec3 color;

public:
    Lambertian() {}
    Lambertian(glm::vec3 _color) : color(_color) {}
    ~Lambertian() {}
    virtual glm::vec3 getReflection(const glm::vec3 &intersect_point, const glm::vec3 &surface_normal) const override
    {
        return intersect_point + surface_normal + rand_unit_vector();
    }
    virtual glm::vec3 getColor() const override
    {
        return color;
    }
};

class Metal : public Material
{
private:
    glm::vec3 color;

public:
    Metal() {}
    Metal(glm::vec3 _color) : color(_color) {}
    ~Metal() {}
    virtual glm::vec3 getReflection(const glm::vec3 &intersect_point, const glm::vec3 &surface_normal) const override
    {
        return intersect_point - 2 * glm::dot(intersect_point, surface_normal) * surface_normal;
    }
    virtual glm::vec3 getColor() const override
    {
        return color;
    }
};