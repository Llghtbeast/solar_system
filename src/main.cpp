#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

/* Prototypes */
void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

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

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.25f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.5f, 0.25f, 0.0f
};
    
int main(void) {
    /* Init the library */
    if (!glfwInit())
    return -1;
    
    /* Create a window */
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello World!", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Adding the current OpenGL context */
    glfwMakeContextCurrent(window);
    
    /* Setup GLEW */
    glewExperimental = GL_TRUE;
    glewInit();
    
    /* Enable v-sync to avoid screen tearing */
    glfwSwapInterval(1);
    
    /* Set callback to update window size */
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    /* Create and compile shaders */
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* Create and use a shader program */
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* Vertex buffer objects */
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Assign attribute descriptions */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    
    /* Loop until user closes window */
    while (!glfwWindowShouldClose(window))
    {
        /* Process inputs */
        processInput(window);
        
        /* Rendering */
        glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Draw triangle */
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // drawCircles();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    // std::cout << "window resized: width: " << width << ", height: " << height << std::endl;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}