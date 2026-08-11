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

uniform vec3 u_Color;

void main()
{
    FragColor = vec4(u_Color, 1.0f);
} 
)glsl";


int main(void) {
    Window window("Solar System Simulation", 1200, 1200);
    Shader shader(vertexShaderSource, fragmentShaderSource);

    SolarSystem solarSystem;

    while (!window.shouldClose())
    {
        window.processInput();

        glm::vec3 background = hexToColor(COLOR_BLACK);
        glClearColor(background.x, background.y, background.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();

        solarSystem.update(window.getDeltaTime());
        solarSystem.draw(&window, &shader);        

        window.swapBuffers();
        window.pollEvents();
    }
    
    return 0;
}