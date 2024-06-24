#version 330 core

// Input vertex attributes
layout(location = 0) in vec3 aPos; // Vertex Position
layout(location = 1) in vec3 aColor; // Vertex color

// Output to fragment shader

out vec3 vertexColor; // Output color to fragment shader


// Uniforms for transformation matrices
uniform mat4 model; // Transform object space coordinates to world space coordinates
uniform mat4 view; // World space coordinates to camera(view) coordinates
uniform mat4 projection; // Camera space coordinates to screen space

void main()
{
    // Apply transformations
    gl_Position = projection * view * model * vec4(aPos,1.0);
    // Pass the color to the fragment shader
    vertexColor = aColor;
}
