#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;
    void processInput();

    float getDeltaTime();

private:
    GLFWwindow* m_window = nullptr;
    int m_width;
    int m_height;
    float m_lastFrameTime = 0.0f;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};