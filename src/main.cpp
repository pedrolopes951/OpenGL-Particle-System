#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Vao.h"
#include "Vbo.h"
#include "Ebo.h"
#include "ShaderManager.h"


// Constants for window dimensions
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;


// Callback function for resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

const float g_vertices[] = {
    // positions         // colors
     0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // top vertex (red)
    -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom left vertex (green)
     0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // bottom right vertex (blue)
};


unsigned int g_indices[] = {
    0,1,2
};

static ShaderManager& initShaderManager()
{
    ShaderManager& shaderManager = ShaderManager::getInstance();

    std::unordered_map<GLenum, std::string> basic_shaders = {
        {GL_VERTEX_SHADER, SHADER_PATH "/vertex_shader.glsl"},
        {GL_FRAGMENT_SHADER, SHADER_PATH "/fragment_shader.glsl"}
    };

    shaderManager.loadShader("basicShaders", basic_shaders);

    return shaderManager;
}


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



    // Set the viewport size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, WIDTH, HEIGHT);

    // Build and compile our shade Program
    Shader basicShader1{SHADER_PATH "/vertex_shader.glsl",SHADER_PATH "/fragment_shader.glsl"};
    
    // Init Shader Manager
    ShaderManager& shaderManager = initShaderManager();


    auto basicShader2 = shaderManager.getShader("basicShaders");
    
    Vao vao;
    vao.bind();
    Vbo vbo(g_vertices, sizeof(g_vertices));
    Ebo ebo(g_indices, sizeof(g_indices));

    vao.setAttribute(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 * sizeof(float)));
    vao.setAttribute(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Unbind the VAO
    vao.unbind();
    

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen with a color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Use the shader program
        //basicShader1.use();
        basicShader2->use();

        // Render the triangle
        // Bind the VAO (it encapsulates the vertex attribute configuration)
        vao.bind();

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

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
