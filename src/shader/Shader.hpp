#pragma once

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "src/tools/Logger.hpp"

namespace gui
{
namespace shader
{

using TextureUnitId = uint32_t;
using TextureTargetType = uint32_t;
using ShaderPartType = uint32_t;

class Shader
{
public:
    Shader(const std::string& shaderPath);

    void setTexture1D(const std::string& name, const TextureUnitId texUnit, const uint32_t texId) const;
    void setTexture2D(const std::string& name, const TextureUnitId texUnit, const uint32_t texId) const;
    void setTexture3D(const std::string& name, const TextureUnitId texUnit, const uint32_t texId) const;
    void setTexture1DArray(const std::string& name, const TextureUnitId texUnit, const uint32_t texId) const;
    void setTexture2DArray(const std::string& name, const TextureUnitId texUnit, const uint32_t texId) const;
    void setInt(const std::string& name, const int32_t value) const;
    void setVec3f(const std::string& name, const glm::vec3& value) const;
    void setVec4f(const std::string& name, const glm::vec4& value) const;
    void setMat4f(const std::string& name, const glm::mat4& value) const;

    void bind() const;
    void unbind() const;

private:
    void setTexture(const std::string& name, const TextureUnitId texUnit, const uint32_t texId,
        const TextureTargetType type) const;
    inline void handleNotFoundLocation(const std::string& name) const;

    uint32_t load(const std::string& shaderPath);
    uint32_t load(const std::string& vertCode, const std::string& fragCode);
    uint32_t linkShaders(int vertShaderId, int fragShaderId);
    uint32_t compileShaderData(const std::string& data, const ShaderPartType shaderType);

    tools::Logger log_;
    uint32_t shaderId_{0};

};
} // namespace shader
} // namespace gui