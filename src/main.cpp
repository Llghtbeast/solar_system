#include "window.hpp"
#include "shader.hpp"
#include "system.hpp"

/* Vertex shader source code */
const char* vertexShaderSource = R"glsl(
#version 330 core
layout(location=0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_Projection;

void main() {
    gl_Position = u_Projection * u_Model * vec4(aPos, 1.0);
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
    Window window("Solar System Simulation", 800, 800);
    Shader shader(vertexShaderSource, fragmentShaderSource);

    SolarSystem solarSystem;

    while (!window.shouldClose())
    {
        window.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();

        solarSystem.update(static_cast<float>(glfwGetTime()));
        solarSystem.draw(&window, &shader);        

        window.swapBuffers();
        window.pollEvents();
    }
    
    return 0;
}