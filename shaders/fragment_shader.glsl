#version 330 core

in vec3 vertexColor; // Input color from vertex shader

out vec4 FragColor; // Output color

void main()
{
    FragColor = vec4(vertexColor, 1.0); // Set the fragment color
}
