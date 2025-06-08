#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath> // For sin, cos, M_PI

// Define M_PI if it's not already defined (common in math.h/cmath)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int WIDTH = 600;
const int HEIGHT = 600;

void drawSphere(double r, int lats, int longs) {
    int i, j;
    for (i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
        double z0 = r * sin(lat0);
        double zr0 = r * cos(lat0);

        double lat1 = M_PI * (-0.5 + (double)i / lats);
        double z1 = r * sin(lat1);
        double zr1 = r * cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double)j / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3d(x * zr0, y * zr0, z0);
            glVertex3d(x * zr0, y * zr0, z0);
            glNormal3d(x * zr1, y * zr1, z1);
            glVertex3d(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}

int main()
{
    // A simple GLFW window creation example
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello GLFW - Sphere", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set up viewport and projection matrix
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set up a simple perspective projection
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); // left, right, bottom, top, near, far

    // Enable depth testing for correct 3D rendering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable lighting for a better looking sphere (optional)
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // Directional light
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glEnable(GL_COLOR_MATERIAL); // Allow glColor to affect material properties

    while (!glfwWindowShouldClose(window))
    {
        // Clear the color buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up model-view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // Move the camera back to see the sphere
        glTranslatef(0.0f, 0.0f, -5.0f);
        // Rotate the sphere for a better view (optional)
        glRotatef(glfwGetTime() * 50.0f, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis

        // Set sphere color
        // Note: OpenGL uses normalized values for colors, so RGB should be in the range [0.0, 1.0]
        glColor3f(1.0f, 0.066f, 0.0f); // Set color to red
        // Draw the sphere
        // r: radius, lats: number of latitudes, longs: number of longitudes
        drawSphere(1.0, 20, 20); // A sphere with radius 1.0, 20 latitudinal and 20 longitudinal segments

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