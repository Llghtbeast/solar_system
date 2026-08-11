#pragma once

#include "constants.hpp"
#include "window.hpp"
#include "mesh.hpp"
#include "celestialBody.hpp"
#include <vector>
#include <unordered_map>

class SolarSystem {
public:
    SolarSystem();

    void update(float dt);
    void draw(Window* window, Shader* shader) const;
    
private:
    Mesh m_mesh;
    std::vector<CelestialBody> m_celestialBodies;
};