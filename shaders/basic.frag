#version 330 core // Specify OpenGL 3.3 Core Profile
out vec4 FragColor; // Final output color for the fragment (pixel)

in vec3 fragColor; // Input color from the vertex shader

void main()
{
    FragColor = vec4(fragColor, 1.0); // Output the received color, with full opacity (alpha = 1.0)
}