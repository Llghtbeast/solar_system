#pragma once

#include "constants.hpp"
#include "window.hpp"
#include "mesh.hpp"
#include "celestialBody.hpp"

#include "tinyformat.h"
#include <pugixml.hpp>
#include <unordered_map>
#include <iostream>

class SolarSystem {
public:
    /**
     * \brief Default constructor, simply create generates mesh, waits for later
     * manual addition of celestial bodies.
     */
    SolarSystem();

    /**
     * \brief Secondary constructor, constructs complete solar system object from
     * XML file.
     * \param filepath path to XML file describing the solar system.
     * \throw runtime_error if error occurs when loading XML file
     */
    SolarSystem(const std::string& filepath);

    void update(float dt);
    void draw(Window* window, Shader* shader) const;
    
    const std::string toString() const;

private:
    Mesh m_mesh;
    std::unordered_map<std::string, CelestialBody> m_celestialBodies;
};