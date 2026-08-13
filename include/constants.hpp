#pragma once

#include <glm/glm.hpp>

// Physical constants
constexpr float EPSILON = 1e-4f;
constexpr float GRAVITATIONAL_CONSTANT = 1.0f;

// Rendering constants
constexpr int SEGMENTS = 64;

// Function template/constexpr helper
// 'inline' prevents unused static function warnings and ODR violations across translation units
inline constexpr glm::vec3 hexToColor(unsigned int hexValue) {
    return glm::vec3(
        static_cast<float>((hexValue >> 16) & 0xFF) / 255.0f, // Red
        static_cast<float>((hexValue >> 8)  & 0xFF) / 255.0f, // Green
        static_cast<float>( hexValue        & 0xFF) / 255.0f   // Blue
    );
}