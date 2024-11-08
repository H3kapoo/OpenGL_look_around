#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <sys/types.h>

namespace gui
{
namespace common
{

enum TextureUnit : uint8_t
{
    _0,  _1,  _2,  _3,  _4,   _5, _6,  _7,
    _8,  _9,  _10, _11, _12, _13, _14, _15,
    _16, _17, _18, _19, _20, _21, _22, _23,
    _24, _25, _26, _27, _28, _29, _30, _31
};

enum TextureType : uint8_t
{
    _1D, _2D, _3D,
    _1DArray, _2DArray,
};

enum TextureWrap : uint8_t
{
    Repeat, MirroredRepeat, ClampToEdge, ClampToBorder
};

enum TextureFilter : uint8_t
{
    Nearest, Linear,
    NearestMipMapNearest, NearestMipMapLinear,
    LinearMipMapNearest, LinearMipMapLinear
};

struct Texture
{
    struct Params
    {
        TextureType type{TextureType::_2D};
        TextureWrap uWrap{TextureWrap::Repeat};
        TextureWrap vWrap{TextureWrap::Repeat};
        glm::vec4 borderColor{1.0f};
        TextureFilter minFilter{TextureFilter::LinearMipMapLinear};
        TextureFilter magFilter{TextureFilter::Linear};
    };

    uint32_t id{0};
    int32_t width{-1};
    int32_t height{-1};
    int32_t numChannels{-1};
    Params params;
};
} // namespace common
} // namespace gui