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


int main(int argc, char* argv[]) {
    Window window("Solar System Simulation", 1200, 1200);
    Shader shader(vertexShaderSource, fragmentShaderSource);

    std::string sceneFile = "scenes/solar.xml";
    if (argc > 1)
        sceneFile = argv[1];

    SolarSystem solarSystem(sceneFile);
    std::cout << "Scene \"" << sceneFile << "\" loaded successfully.\n";
    std::cout << solarSystem.toString();

    while (!window.shouldClose())
    {
        window.processInput();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();

        solarSystem.update(0.001 * window.getDeltaTime());
        solarSystem.draw(&window, &shader);        

        window.swapBuffers();
        window.pollEvents();
    }
    
    return 0;
}