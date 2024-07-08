#include "ShaderManager.h"
#include <iostream>

ShaderManager &ShaderManager::getInstance()
{
    static ShaderManager instance; // Create here the static instance that will be active for the whole duration of the program
    return instance;
}

std::shared_ptr<Shader> &ShaderManager::loadShader(const std::string &name, const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    m_shaders[name] = std::make_shared<Shader>(vertexShaderPath,fragmentShaderPath);

    return m_shaders[name];
}

std::shared_ptr<Shader> &ShaderManager::loadShader(const std::string &name, const std::unordered_map<GLenum, std::string> &shaderPaths)
{
    m_shaders[name] = std::make_shared<Shader>(shaderPaths);
    

    return m_shaders[name];
}

std::shared_ptr<Shader> &ShaderManager::getShader(const std::string &name)
{
    auto it = m_shaders.find(name);
    if (it != m_shaders.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Shader not found: " + name);
    }}

void ShaderManager::clear()
{
    // erase all elements in the shader map
    m_shaders.clear();
}
