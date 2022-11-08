#pragma once
#include <glm/vec3.hpp>
#include "Ray.hpp"
#include "Utility.hpp"

glm::vec3 randomUnitVector();

class Material
{
private:
public:
    virtual Ray getReflection(const glm::vec3 &ray_direction, const glm::vec3 &surface_normal, const glm::vec3& P) const = 0;
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
    virtual Ray getReflection(const glm::vec3 &ray_in_direction, const glm::vec3 &surface_normal, const glm::vec3& P) const override
    {
        glm::vec3 reflection_direction = surface_normal + randomUnitVector();
        float threshold = 1e-8;

        // Diffuse material reflect randomly across the normal unrelated to the incoming ray
        // if this random direction cancels out the surface normal, just reflect along the surface normal 
        if (reflection_direction.r < threshold && reflection_direction.r < threshold && reflection_direction.b < threshold)
            reflection_direction = surface_normal;
            
        return Ray(P, reflection_direction);
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
    virtual Ray getReflection(const glm::vec3 &ray_in_direction, const glm::vec3 &surface_normal, const glm::vec3& P) const override
    {
        return Ray(P,ray_in_direction - 2 * glm::dot(glm::normalize(ray_in_direction), surface_normal) * surface_normal);
    }
    virtual glm::vec3 getColor() const override
    {
        return color;
    }
};