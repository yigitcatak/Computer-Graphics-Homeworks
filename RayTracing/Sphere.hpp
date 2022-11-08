#pragma once
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "Hittable.hpp"
#include "Ray.hpp"
#include "Material.hpp"
class Sphere : public Hittable
{
private:
    glm::vec3 center;
    float radius;
    std::shared_ptr<Material> material_ptr;

public:
    Sphere();
    Sphere(glm::vec3 _center, float _radius, std::shared_ptr<Material> mat_ptr) : center(_center), radius(_radius), material_ptr(mat_ptr) {}
    ~Sphere();
    const glm::vec3 getCenter() const { return center; }
    virtual bool isHit(const Ray &r, const double threshold, hitRecord& record) const override; // this is how to use virtual functions
    virtual glm::vec3 getSurfaceNormal(const Ray &r, double z_coord) const override;
    virtual std::shared_ptr<Material> getMaterialPtr() const override;
};

Sphere::Sphere() {}

Sphere::~Sphere() {}

bool Sphere::isHit(const Ray &r, const double threshold, hitRecord& record) const
{
    /* A vector's dot product with itself is the square of its magnitude
    (M + nx - center) * (M + nx - center) == r^2 -> this eq should hold for hit
    since M and center are constants, call them constant const_val, in this case our eq. becomes
    (nx - const_val) ^ 2 - r^2 = 0, for hit, discriminant of this eq should be greater than 0.
    */
    const auto const_val = r.getOrig() - center;
    const auto a = glm::dot(r.getDir(), r.getDir());
    const auto b = 2 * (glm::dot(const_val, r.getDir()));
    const auto c = glm::dot(const_val, const_val) - (radius * radius);

    const auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false;

    double root = (-b-sqrt(discriminant)) / (2.0*a);
    if (root < threshold) return false;

    record.t = root;
    record.P = r.at(root);
    glm::vec3 normal = (record.P - center)/radius;
    record.setFaceNormal(r, normal);
    record.material_ptr = material_ptr;
    return true;
}

glm::vec3 Sphere::getSurfaceNormal(const Ray &r, double z_coord) const
{
    return glm::normalize(r.at(z_coord) - center);
}

std::shared_ptr<Material> Sphere::getMaterialPtr() const
{
    return material_ptr;
}
