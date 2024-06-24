#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

// Constants for window dimensions
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;


// Callback function for resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Function to render a triangle
// void draw_triangle()
// {
//     glBegin(GL_TRIANGLES); // Begin drawing triangles
//         glColor3f(1.0f, 0.0f, 0.0f); // Red color
//         glVertex2f(-0.5f, -0.5f);    // Vertex 1
//         glColor3f(0.0f, 1.0f, 0.0f); // Green color
//         glVertex2f(0.5f, -0.5f);     // Vertex 2
//         glColor3f(0.0f, 0.0f, 1.0f); // Blue color
//         glVertex2f(0.0f, 0.5f);      // Vertex 3
//     glEnd(); // End drawing triangles
// }

const float g_vertices[] = {
     // position          // colors
     0.0f,  0.5f, 0.0f,   1.0f,0.0f,0.0f, // top vertex (red)
    -0.5f, -0.5f, 0.0f,   0.0f,1.0f,0.0f, // bottom left vertex (green)
     0.5f, -0.5f, 0.0f,   0.0f,0.0f,1.0f // bottom right vertex (blue)
};

unsigned int g_indices[] = {
    0,1,2
};


int main(int argc, char** argv)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set GLFW window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // Use compatibility profile, this allows older code (core and compatibility profile) deprecated to run

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Particle System", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);


    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << "\n";
        return -1;
    }

    std::cout << "GLEW initialized successfully\n";

    // Print OpenGL information
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";

    // Set the viewport size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, WIDTH, HEIGHT);

    // Build and compile our shade Program
    Shader shader{SHADER_PATH "/vertex_shader.glsl",SHADER_PATH "/fragment_shader.glsl"};
    
    // Set up vertex data and buffers and configure vertex atttributes
    unsigned int vbo,vao,ebo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertices), g_vertices ,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(g_indices), g_indices ,GL_STATIC_DRAW);


    //Position attributes
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO
    glBindVertexArray(0);

    

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen with a color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Use the shader progra,

        // Render the triangle
        // Bind the VAO (it encapsulates the vertex attribute configuration)
        glBindVertexArray(vao);

        // Draw the triangle using the EBO (index buffer)
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // Check for OpenGL errors
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL Error: " << error << "\n";
        }

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }


    // Clean up
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);
    glDeleteBuffers(1,&ebo);

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
