#include "Shader.hpp"
#include "src/common/Texture.hpp"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

namespace gui
{
namespace shader
{
Shader::Shader(const std::string& shaderPath)
    : log_{"Shader(" + shaderPath +")"}
    , shaderId_(load(shaderPath))
{}

void Shader::setTexture1D(const std::string& name, const TextureUnit texUnit, const uint32_t texId) const
{
    setTexture(name, texUnit, texId, TextureType::_1D);
}

void Shader::setTexture2D(const std::string& name, const TextureUnit texUnit, const uint32_t texId) const
{
    setTexture(name, texUnit, texId, TextureType::_2D);
}

void Shader::setTexture3D(const std::string& name, const TextureUnit texUnit, const uint32_t texId) const
{
    setTexture(name, texUnit, texId, TextureType::_3D);
}

void Shader::setTexture1DArray(const std::string& name, const TextureUnit texUnit,
    const uint32_t texId) const
{
    setTexture(name, texUnit, texId, TextureType::_1DArray);
}

void Shader::setTexture2DArray(const std::string& name, const TextureUnit texUnit,
    const uint32_t texId) const
{
    setTexture(name, texUnit, texId, TextureType::_2DArray);
}

void Shader::setInt(const std::string& name, const int32_t value) const
{
    int32_t loc = glGetUniformLocation(shaderId_, name.c_str());
    if (loc == -1)
    {
        return handleNotFoundLocation(name);
    }
    glUniform1i(loc, value);
}

void Shader::setVec3f(const std::string& name, const glm::vec3& value) const
{
    int32_t loc = glGetUniformLocation(shaderId_, name.c_str());
    if (loc == -1)
    {
        return handleNotFoundLocation(name);
    }
    glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::setVec4f(const std::string& name, const glm::vec4& value) const
{
    int32_t loc = glGetUniformLocation(shaderId_, name.c_str());
    if (loc == -1)
    {
        return handleNotFoundLocation(name);
    }
    glUniform4f(loc, value.x, value.y, value.z, value.w);
}

void Shader::setMat4f(const std::string& name, const glm::mat4& value) const
{
    int32_t loc = glGetUniformLocation(shaderId_, name.c_str());
    if (loc == -1)
    {
        return handleNotFoundLocation(name);
    }
    constexpr uint32_t transposeMatrix = GL_FALSE;
    glUniformMatrix4fv(loc, 1, transposeMatrix, glm::value_ptr(value));
}

void Shader::setTexture(const std::string& name, const TextureUnit texUnit, const uint32_t texId,
    const TextureType type) const
{
    int32_t maxTextureUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
    if (texUnit+1 > maxTextureUnits)
    {
        log_.error("GPU not able to support more than %d texture units. Tried to use unit %d",
            maxTextureUnits, texUnit);
        return;
    }

    // Shader needs texture unit location in range from [0..maxUnits], not from [GL_TEXTURE0..maxGL_TEXTURE]
    setInt(name, (GL_TEXTURE0+texUnit) - GL_TEXTURE0);
    glActiveTexture(GL_TEXTURE0 + texUnit);

    uint32_t glTarget{0};
    switch (type)
    {
        case common::TextureType::_1D:
            glTarget = GL_TEXTURE_1D;
            break;
        case common::TextureType::_2D:
            glTarget = GL_TEXTURE_2D;
            break;
        case common::TextureType::_3D:
            glTarget = GL_TEXTURE_3D;
            break;
        case common::TextureType::_1DArray:
            glTarget = GL_TEXTURE_1D_ARRAY;
            break;
        case common::TextureType::_2DArray:
            glTarget = GL_TEXTURE_2D_ARRAY;
            break;
        default:
            glTarget = GL_TEXTURE_2D;
    }
    glBindTexture(glTarget, texId);
}

inline void Shader::handleNotFoundLocation(const std::string& name) const
{
    log_.error("Uniform \"%s\" not found", name.c_str());
}

void Shader::bind() const
{
    glUseProgram(shaderId_);
}
void Shader::unbind() const
{
    glUseProgram(0);
}

uint32_t Shader::load(const std::string& shaderPath)
{
    // shaderIdPtr idPtr = shaderPathToGenId[shaderPath];
    // if (idPtr != nullptr) { return idPtr; }

    std::ifstream shaderFile(shaderPath);
    if (!shaderFile)
    {
        log_.error("Could not open shader file at %s\n", shaderPath.c_str());
        return 0;
        // return nullptr;
    }

    std::stringstream stream;
    stream << shaderFile.rdbuf();
    std::string content = stream.str();
    shaderFile.close();

    const size_t fragCutoff = content.find("/// frag ///\n"); /* WRN: LF ending handled only */

    std::string vertData{content.begin(), content.begin() + fragCutoff};
    std::string fragData{content.begin() + fragCutoff, content.end()};

    return load(vertData, fragData);
}

uint32_t Shader::load(const std::string& vertCode, const std::string& fragCode)
{
    // shaderIdPtr idPtr = shaderPathToGenId[key];
    // if (idPtr != nullptr) { return idPtr; }

    // shaderIdPtr newId = new shaderId;
    uint32_t shaderId = linkShaders(
        compileShaderData(vertCode, GL_VERTEX_SHADER),
        compileShaderData(fragCode, GL_FRAGMENT_SHADER));

    // shaderPathToGenId[key] = newId;
    // if (*newId != -1) { utils::printlni("Loaded shader Id {} from key {}", *newId, key.c_str()); }
    return shaderId;
}

uint32_t Shader::linkShaders(int vertShaderId, int fragShaderId)
{
    if (vertShaderId == 0 || fragShaderId == 0) { return 0; }

    auto shaderId = glCreateProgram();

    glAttachShader(shaderId, vertShaderId);
    glAttachShader(shaderId, fragShaderId);
    glLinkProgram(shaderId);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderId, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderId, 512, nullptr, infoLog);
        log_.error("Could not link program:\n\t%s\n", infoLog);
        return 0;
    }

    glDeleteShader(vertShaderId);
    glDeleteShader(fragShaderId);

    return shaderId;
}

uint32_t Shader::compileShaderData(const std::string& data, int32_t shaderType)
{
    const char* src = data.c_str();
    uint32_t shaderPart = glCreateShader(shaderType);
    glShaderSource(shaderPart, 1, &src, NULL);
    glCompileShader(shaderPart);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderPart, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderPart, 512, NULL, infoLog);
        std::string type = shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAG";
        log_.error("Compile failed for shader %s because:\n\t%s", type.c_str(), infoLog);
        return 0;
    }

    return shaderPart;
}
} // namespace shader
} // namesapce gui