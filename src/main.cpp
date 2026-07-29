#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

    /* Enable v-sync to avoid screen tearing */
    glfwSwapInterval(1);

    /* Loop until user closes window */
    while (!glfwWindowShouldClose(window))
    {
        /* Rendering */
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}