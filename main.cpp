#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    // A simple GLFW window creation example
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello GLFW", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        // Render here (for now, just clear the window)
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "GLFW window closed successfully." << std::endl;

    return 0;
}