#include "TextureLoader.hpp"
#include <GL/glext.h>

#define STB_IMAGE_IMPLEMENTATION
#include "src/vendor/stb_image.h"

#include "src/common/Texture.hpp"

namespace gui
{
namespace assetloaders
{
TextureLoader& TextureLoader::get()
{
    static TextureLoader instance;
    return instance;
}

TextureLoader::TextureLoader()
    : log_("TextureLoader")
{
    stbi_set_flip_vertically_on_load(true);
    log_.info("Created!");
}

common::Texture TextureLoader::loadTexture(const std::string &resPath, const common::Texture::Params& params)
{
    return loadInternal(resPath, params);
}

common::Texture TextureLoader::loadInternal(const std::string &resPath,
    const common::Texture::Params& params)
{
    common::Texture texData;
    unsigned char* data = stbi_load(resPath.c_str(), &texData.width, &texData.height, &texData.numChannels, 0);
    if (!data)
    {
        log_.error("Failed to load texture. Check path correctness for %s", resPath.c_str());
        return texData;
    }

    uint32_t glColorFormat = resPath.ends_with(".png") ? GL_RGBA : GL_RGB;

    uint32_t glTarget{0};
    switch (params.type)
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

    uint32_t uWrap{0}, vWrap{0};
    switch (params.uWrap)
    {
        case common::TextureWrap::Repeat:
            uWrap = GL_REPEAT;
            break;
        case common::TextureWrap::MirroredRepeat:
            uWrap = GL_MIRRORED_REPEAT;
            break;
        case common::TextureWrap::ClampToEdge:
            uWrap = GL_CLAMP_TO_EDGE;
            break;
        case common::TextureWrap::ClampToBorder:
            uWrap = GL_CLAMP_TO_BORDER;
            break;
        default:
            uWrap = GL_REPEAT;
    }

    switch (params.vWrap)
    {
        case common::TextureWrap::Repeat:
            vWrap = GL_REPEAT;
            break;
        case common::TextureWrap::MirroredRepeat:
            vWrap = GL_MIRRORED_REPEAT;
            break;
        case common::TextureWrap::ClampToEdge:
            vWrap = GL_CLAMP_TO_EDGE;
            break;
        case common::TextureWrap::ClampToBorder:
            vWrap = GL_CLAMP_TO_BORDER;
            break;
        default:
            vWrap = GL_REPEAT;
    }

    uint32_t minFilter{0}, magFilter{0};
    switch (params.minFilter)
    {
        case common::TextureFilter::Nearest:
            minFilter = GL_NEAREST;
            break;
        case common::TextureFilter::Linear:
            minFilter = GL_LINEAR;
            break;
        case common::TextureFilter::NearestMipMapNearest:
            minFilter = GL_NEAREST_MIPMAP_NEAREST;
            break;
        case common::TextureFilter::NearestMipMapLinear:
            minFilter = GL_NEAREST_MIPMAP_LINEAR;
            break;
        case common::TextureFilter::LinearMipMapNearest:
            minFilter = GL_LINEAR_MIPMAP_NEAREST;
            break;
        case common::TextureFilter::LinearMipMapLinear:
            minFilter = GL_LINEAR_MIPMAP_LINEAR;
            break;
        default:
            minFilter = GL_LINEAR;
    }

    switch (params.magFilter)
    {
        case common::TextureFilter::Nearest:
            magFilter = GL_NEAREST;
            break;
        case common::TextureFilter::Linear:
            magFilter = GL_LINEAR;
            break;
        case common::TextureFilter::NearestMipMapNearest:
        case common::TextureFilter::NearestMipMapLinear:
        case common::TextureFilter::LinearMipMapNearest:
        case common::TextureFilter::LinearMipMapLinear:
            // Not supported for mag filter
        default:
            magFilter = GL_LINEAR;
    }

    float borderColor[] = {params.borderColor.r, params.borderColor.g, params.borderColor.b, params.borderColor.a};
    glGenTextures(1, &texData.id);
    glBindTexture(glTarget, texData.id);
    glTexParameteri(glTarget, GL_TEXTURE_WRAP_S, uWrap);
    glTexParameteri(glTarget, GL_TEXTURE_WRAP_T, vWrap);
    glTexParameteri(glTarget, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(glTarget, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameterfv(glTarget, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexImage2D(glTarget, 0, glColorFormat, texData.width, texData.height, 0, glColorFormat,
        GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(glTarget);

    stbi_image_free(data);

    log_.info("Loaded texture: %s (id:%d %dx%dx%d)", resPath.c_str(), texData.id, texData.width, texData.height,
        texData.numChannels);

    return texData;
}
} // namespace assetloaders
} // namespace gui