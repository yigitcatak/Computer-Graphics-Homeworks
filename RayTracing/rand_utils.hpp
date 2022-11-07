#include <random>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

// returns random real in [0,1)
double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

double random_double(double min, double max)
{
    return (min + (max - min) * random_double());
}

glm::vec3 random_vector()
{
    return glm::vec3(random_double(), random_double(), random_double());
}

glm::vec3 random_vector(double min, double max)
{
    return glm::vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

glm::vec3 rand_unit_vector()
{
    auto p = random_vector(-1, 1);
    return glm::normalize(p);
}