#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "Shader.h"


class ShaderManager
{
private:

    // Hold the shaders     
    ShaderManager(/* args */){};
    // Delete the copy construtor and the operator= to prevent copy the singleton class
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;
    ~ShaderManager(){this->clear();}

    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;

public:
    // Static method to get the singletong instance
    static ShaderManager& getInstance();

    // Method to load and get shaders
    std::shared_ptr<Shader>& loadShader(const std::string& name, const std::string& vertexShaderPath,const std::string& fragmentShaderPath);
    std::shared_ptr<Shader>& loadShader(const std::string& name, const std::unordered_map<GLenum, std::string>& shaderPaths);
    std::shared_ptr<Shader>& getShader(const std::string& name);
    void clear();


};

