// OpenGL Shading Language

#version 330 core // Specify OpenGL 3.3 Core Profile
layout (location = 0) in vec3 aPos;   // Vertex position (layout location 0)
layout (location = 1) in vec3 aColor;  // Vertex color (layout location 1)

out vec3 fragColor; // Output color to the fragment shader

uniform mat4 model;      // Model matrix (object to world space)
uniform mat4 view;       // View matrix (world to camera space)
uniform mat4 projection; // Projection matrix (camera to clip space)

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); // Transform vertex position
    fragColor = aColor; // Pass the input color directly to the fragment shader
}