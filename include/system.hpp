#pragma once

#include "window.hpp"
#include "mesh.hpp"
#include "celestialBody.hpp"
#include <vector>
#include <unordered_map>

#define SEGMENTS 64

class SolarSystem {
public:
    SolarSystem();

    void update(float time);
    void draw(Window* window, Shader* shader) const;
    
private:
    Mesh m_mesh;
    std::unordered_map<std::string, CelestialBody> m_celestialBodies;
};