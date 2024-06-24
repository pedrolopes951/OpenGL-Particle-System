#version 330 core

// Input from vertex shader
in vec3 vertexColor; // Input color vertex shader

// Ouput color
out vec4 FragColor;

void main()
{
    // Set the fragment color
    FragColor= vec4(vertexColor, 1.0);
}