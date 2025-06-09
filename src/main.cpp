#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>  // For sin, cos, M_PI
#include <vector> // For std::vector

// Define M_PI if it's not already defined (common in math.h/cmath)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int WIDTH = 600;
const int HEIGHT = 600;

// Class to hold UV Sphere geometry data
class SphereData
{
public:
    std::vector<float> vertices;       // x, y, z coordinates
    std::vector<float> normals;        // normal vectors
    std::vector<float> texCoords;      // u, v texture coordinates
    std::vector<unsigned int> indices; // indices for indexed drawing

    // Constructor to generate sphere data
    SphereData(float radius, int latitudes, int longitudes)
    {
        generateSphere(radius, latitudes, longitudes);
    }

private:
    void generateSphere(float radius, int latitudes, int longitudes)
    {
        // Clear any existing data
        vertices.clear();
        normals.clear();
        texCoords.clear();
        indices.clear();

        // Generate vertices, normals, and texture coordinates
        for (int lat = 0; lat <= latitudes; lat++)
        {
            float theta = lat * M_PI / latitudes;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            for (int lon = 0; lon <= longitudes; lon++)
            {
                float phi = lon * 2 * M_PI / longitudes;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);

                // Calculate vertex position
                float x = radius * sinTheta * cosPhi;
                float y = radius * sinTheta * sinPhi;
                float z = radius * cosTheta;

                // Store vertex position
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                // Store normal (normalized vertex position for a sphere)
                normals.push_back(sinTheta * cosPhi);
                normals.push_back(sinTheta * sinPhi);
                normals.push_back(cosTheta);

                // Store texture coordinates
                texCoords.push_back(static_cast<float>(lon) / longitudes);
                texCoords.push_back(static_cast<float>(lat) / latitudes);
            }
        }

        // Generate indices for triangle strips
        for (int lat = 0; lat < latitudes; lat++)
        {
            for (int lon = 0; lon < longitudes; lon++)
            {
                // Calculate indices for quad
                unsigned int first = lat * (longitudes + 1) + lon;
                unsigned int second = first + longitudes + 1;

                // First triangle
                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                // Second triangle
                indices.push_back(first + 1);
                indices.push_back(second);
                indices.push_back(second + 1);
            }
        }
    }
};

// Function to draw a sphere using the SphereData
void drawSphere(const SphereData &sphere)
{
    // Draw using triangle primitives
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < sphere.indices.size(); i += 3)
    {
        // First vertex of triangle
        unsigned int idx1 = sphere.indices[i] * 3;
        glNormal3f(sphere.normals[idx1], sphere.normals[idx1 + 1], sphere.normals[idx1 + 2]);
        glVertex3f(sphere.vertices[idx1], sphere.vertices[idx1 + 1], sphere.vertices[idx1 + 2]);

        // Second vertex of triangle
        unsigned int idx2 = sphere.indices[i + 1] * 3;
        glNormal3f(sphere.normals[idx2], sphere.normals[idx2 + 1], sphere.normals[idx2 + 2]);
        glVertex3f(sphere.vertices[idx2], sphere.vertices[idx2 + 1], sphere.vertices[idx2 + 2]);

        // Third vertex of triangle
        unsigned int idx3 = sphere.indices[i + 2] * 3;
        glNormal3f(sphere.normals[idx3], sphere.normals[idx3 + 1], sphere.normals[idx3 + 2]);
        glVertex3f(sphere.vertices[idx3], sphere.vertices[idx3 + 1], sphere.vertices[idx3 + 2]);
    }
    glEnd();
}

int main()
{
    // A simple GLFW window creation example
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello GLFW - UV Sphere", nullptr, nullptr);
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

    // Enable lighting for a better looking sphere
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = {1.0f, 1.0f, 1.0f, 0.0f}; // Directional light
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glEnable(GL_COLOR_MATERIAL); // Allow glColor to affect material properties

    // Create our sphere data
    SphereData sphereData(1.0f, 50, 50); // radius=1.0, Increase for more detail 

    while (!glfwWindowShouldClose(window))
    {
        // Clear the color buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up model-view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // Move the camera back to see the sphere
        glTranslatef(0.0f, 0.0f, -5.0f);
        // Rotate the sphere for a better view
        glRotatef(glfwGetTime() * 50.0f, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis

        // Set sphere color
        glColor3f(1.0f, 0.066f, 0.0f); // Set color to red

        // Draw the sphere using our SphereData
        drawSphere(sphereData);

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