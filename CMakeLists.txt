cmake_minimum_required(VERSION 3.10) 
project(OpenGLParticleSystem)

set(CMAKE_CXX_STANDARD 17)

# Set policy to use GLVND by default when available
cmake_policy(SET CMP0072 NEW)

# Finds packages necessary for this project
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# Define the shader path macro
add_compile_definitions(SHADER_PATH="${CMAKE_SOURCE_DIR}/shaders")



# Includes directories for OpenGL, GLEW and GLFW
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

#add the executable and the specifies the source files
add_executable(${PROJECT_NAME} src/main.cpp
                               src/Shader.cpp
                               src/ErrorHandling.cpp
                               src/Vao.cpp
                               src/Vbo.cpp
                               src/Ebo.cpp)

#links the executable with all the necessary libraries
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glfw)
