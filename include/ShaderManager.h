#pragma once
#include <unordered_map>
#include <string>
#include "Shader.h"

class ShaderManager
{
private:
    // Hold the shaders
    std::unordered_map<std::string,Shader> m_mapShaders;     

public:
    ShaderManager(/* args */){};
    ~ShaderManager(){};

    // Load shaders into the map
    void load(const std::string& name,const std::string& pathShader);
};

