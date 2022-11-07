#pragma once

#include <glm/vec3.hpp>

class Ray
{
private:
    glm::vec3 origin;    // M
    glm::vec3 direction; // n
public:
    Ray();
    Ray(glm::vec3 orig, glm::vec3 dir) : origin(orig), direction(dir) {}
    ~Ray() {}
    const glm::vec3 &getOrig() const { return origin; }
    const glm::vec3 &getDir() const { return direction; } // if you don't init get functions like this
    // accessing this method from const reference objects would be impossible

    // calculates M + nx
    glm::vec3 at(float x) const
    {
        return (origin + (direction * x));
    }
};
