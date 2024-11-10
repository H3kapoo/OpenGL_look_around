#pragma once

#include <cstdint>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace gui
{
namespace common
{
struct Texture
{
    struct Params
    {
        uint32_t target           {GL_TEXTURE_2D};
        uint32_t uWrap            {GL_REPEAT};
        uint32_t vWrap            {GL_REPEAT};
        uint32_t minFilter        {GL_LINEAR_MIPMAP_LINEAR};
        uint32_t magFilter        {GL_LINEAR};
        glm::vec4 borderColor     {1.0f};
        float anisotropicFiltering{2.0f};
    };

    uint32_t id{0};
    int32_t width{-1};
    int32_t height{-1};
    int32_t numChannels{-1};
    Params params;
};
} // namespace common
} // namespace gui