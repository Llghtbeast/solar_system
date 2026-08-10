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

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    float getAspectRatio() const { 
        return m_height > 0 ? static_cast<float>(m_width) / static_cast<float>(m_height) : 1.0f; 
    }

    float getDeltaTime();

private:
    GLFWwindow* m_window = nullptr;
    int m_width;
    int m_height;
    float m_lastFrameTime = 0.0f;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};