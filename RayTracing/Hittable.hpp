#pragma once
#include <memory>
#include "Ray.hpp"
#include "Material.hpp"

class Hittable;

struct hitRecord
{
    std::shared_ptr<Material> material_ptr;
    glm::vec3 P;
    float t;

    glm::vec3 surface_normal;
    bool front_face;

    inline void setFaceNormal(const Ray& r, const glm::vec3& normal) {
        front_face = dot(r.getDir(), normal) < 0;
        surface_normal = front_face ? normal :-normal;
    }
};

class Hittable
{
private:
public:
    // returns the z coordinate if a ray hits to a hittable
    virtual bool isHit(const Ray &r, const double threshold, hitRecord& record) const = 0;
    virtual glm::vec3 getSurfaceNormal(const Ray & r, double z_coord) const = 0;
    virtual std::shared_ptr<Material> getMaterialPtr() const = 0;
};
