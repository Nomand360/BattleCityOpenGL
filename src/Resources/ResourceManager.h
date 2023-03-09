#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <memory>
#include <map>

namespace Renderer {
    class ShaderProgram;
}

class ResourceManager
{
public:
    ResourceManager(const std::string &executablePath);
    ~ResourceManager() = default;

    ResourceManager() = delete;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager&operator=(ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager&operator=(ResourceManager&&) = delete;

    std::shared_ptr<Renderer::ShaderProgram> loadShagers(const std::string &shaderName, const std::string &vertexPath, const std::string &fragmentPath);

    std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string &shaderName);

    void loadTexture(const std::string &textureName, const std::string &texturePath);
private:
    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> shaderProgramsMap;
    shaderProgramsMap m_shaderPrograms;
    std::string m_path;

    std::string getFileString(const std::string &reletiveFilaePAth) const;
};

#endif // RESOURCEMANAGER_H
