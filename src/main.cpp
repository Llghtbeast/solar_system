#include "window.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include <vector>

/* Vertex shader source code */
const char* vertexShaderSource = R"glsl(
#version 330 core
layout(location=0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
)glsl";

/* Fragment shader source code */
const char *fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
)glsl";

int main(void) {
    Window window("Solar System Simulation", 800, 600);
    Shader shader(vertexShaderSource, fragmentShaderSource);

    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.25f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, 0.25f, 0.0f
    };
    Mesh mesh(vertices);

    while (!window.shouldClose())
    {
        window.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        mesh.draw();

        window.swapBuffers();
        window.pollEvents();
    }
    
    return 0;
}