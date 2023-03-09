#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::ResourceManager(const std::string &executablePath)
{
    size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0 , found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShagers(const std::string &shaderName, const std::string &vertexPath, const std::string &fragmentPath)
{
    std::string vertexString = getFileString(vertexPath);
    if(vertexString.empty()){
        std::cerr << "No vertex shader!" << std::endl;
        return nullptr;
    }

    std::string fragmentString = getFileString(fragmentPath);
    if(fragmentString.empty()){
        std::cerr << "No fragment shader!" << std::endl;
        return nullptr;
    }
    const auto &shader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;

    if(shader->isCompiled()){
        return shader;
    }
    std::cerr << "Error load shader!" << std::endl;
    return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string &shaderName)
{
    const auto fShader = m_shaderPrograms.find(shaderName);
    if(fShader != m_shaderPrograms.end()){
        return fShader->second;
    }
    std::cerr << "Cant find shader: " << shaderName << std::endl;
    return nullptr;
}

void ResourceManager::loadTexture(const std::string &textureName, const std::string &texturePath)
{
    int channels = 0;
    int width = 0;
    int height = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load((m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);
    if(!pixels){
        std::cerr << "Cant load image: " << texturePath << std::endl;
        return;
    }
    stbi_image_free(pixels);
}

std::string ResourceManager::getFileString(const std::string &reletiveFilaePAth) const
{
    std::fstream f;
    f.open(m_path + '/' + reletiveFilaePAth, std::ios::in | std::ios::binary);
    if(!f.is_open()){
        std::cerr << "Failed to open file: " << reletiveFilaePAth << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}
