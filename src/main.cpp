#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>  // For sin, cos, M_PI
#include <vector> // For std::vector
#include "Shader.h"

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

    // For modern OpenGL
    unsigned int VAO, VBO, EBO;
    bool initialized = false;

    // Constructor to generate sphere data
    SphereData(float radius, int latitudes, int longitudes)
    {
        generateSphere(radius, latitudes, longitudes);
    }

    // Initialize OpenGL buffers
    void setupBuffers()
    {
        if (initialized)
            return;

        // Create a combined array of position, normal, and texture coords
        std::vector<float> vertexData;
        for (size_t i = 0; i < vertices.size() / 3; i++)
        {
            // Position (x, y, z)
            vertexData.push_back(vertices[i * 3]);
            vertexData.push_back(vertices[i * 3 + 1]);
            vertexData.push_back(vertices[i * 3 + 2]);

            // Normal (nx, ny, nz)
            vertexData.push_back(normals[i * 3]);
            vertexData.push_back(normals[i * 3 + 1]);
            vertexData.push_back(normals[i * 3 + 2]);

            // Texture coords (u, v)
            vertexData.push_back(texCoords[i * 2]);
            vertexData.push_back(texCoords[i * 2 + 1]);
        }

        // Generate and bind VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Generate and bind VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

        // Generate and bind EBO
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture coords attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Unbind
        glBindVertexArray(0);
        initialized = true;
    }

    // Clean up resources
    void cleanup()
    {
        if (initialized)
        {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            initialized = false;
        }
    }

    ~SphereData()
    {
        cleanup();
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

// Function to draw a sphere using the SphereData and modern OpenGL
void drawSphere(const SphereData &sphere)
{
    if (!sphere.initialized)
    {
        // Cast away constness to set up buffers if not done already
        const_cast<SphereData &>(sphere).setupBuffers();
    }

    // Bind VAO and draw
    glBindVertexArray(sphere.VAO);
    glDrawElements(GL_TRIANGLES, sphere.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

int main()
{
    // A simple GLFW window creation example
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW for OpenGL core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello GLFW - UV Sphere", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set up viewport
    glViewport(0, 0, WIDTH, HEIGHT);

    // Enable depth testing for correct 3D rendering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Create our sphere data
    SphereData sphereData(1.0f, 50, 50); // radius=1.0, Increase for more detail
    Shader* basicShader = new Shader("shaders/basic.vert", "shaders/basic.frag");

    while (!glfwWindowShouldClose(window))
    {
        // Clear the color buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate model, view, projection matrices
        // Model matrix (rotating sphere)
        float rotationAngle = glfwGetTime() * 50.0f;
        float radians = rotationAngle * M_PI / 180.0f;
        float cosAngle = cos(radians);
        float sinAngle = sin(radians);

        // Simple model matrix for rotation around Y axis
        float modelMatrix[16] = {
            cosAngle, 0.0f, sinAngle, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            -sinAngle, 0.0f, cosAngle, 0.0f,
            0.0f, 0.0f, -5.0f, 1.0f // Translate back 5 units
        };

        // Simple view matrix (identity for now)
        float viewMatrix[16] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f};

        // Perspective projection matrix
        float aspectRatio = (float)WIDTH / (float)HEIGHT;
        float fov = 45.0f * M_PI / 180.0f;
        float near = 0.1f;
        float far = 100.0f;
        float tanHalfFov = tan(fov / 2.0f);

        float projMatrix[16] = {
            1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f / tanHalfFov, 0.0f, 0.0f,
            0.0f, 0.0f, -(far + near) / (far - near), -1.0f,
            0.0f, 0.0f, -(2.0f * far * near) / (far - near), 0.0f};

        // Use shader program and set uniforms
        basicShader->use();
        basicShader->setMat4("model", modelMatrix);
        basicShader->setMat4("view", viewMatrix);
        basicShader->setMat4("projection", projMatrix);

        // Set light properties
        // float lightPos[3] = {1.0f, 1.0f, 1.0f};
        // float lightColor[3] = {1.0f, 1.0f, 1.0f};
        // float objectColor[3] = {1.0f, 0.066f, 0.0f}; // Red color

        // basicShader.setMat4("lightPos", lightPos);
        // basicShader.setMat4("lightColor", lightColor);
        // basicShader.setMat4("objectColor", objectColor);

        // Draw the sphere using our SphereData
        drawSphere(sphereData);

        // Swap buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up resources
    sphereData.cleanup();

    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "GLFW window closed successfully." << std::endl;

    return 0;
}