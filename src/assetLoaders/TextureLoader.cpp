#include "TextureLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "src/vendor/stb_image.h"

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
    float borderColor[] = {params.borderColor.r, params.borderColor.g, params.borderColor.b, params.borderColor.a};

    glGenTextures(1, &texData.id);
    glBindTexture(params.target, texData.id);
    glTexParameteri(params.target, GL_TEXTURE_WRAP_S, params.uWrap);
    glTexParameteri(params.target, GL_TEXTURE_WRAP_T, params.vWrap);
    glTexParameteri(params.target, GL_TEXTURE_MIN_FILTER, params.minFilter);
    glTexParameteri(params.target, GL_TEXTURE_MAG_FILTER, params.magFilter);
    glTexParameterfv(params.target, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameterf(params.target, GL_TEXTURE_MAX_ANISOTROPY, params.anisotropicFiltering);

    // or 1D/3D.. to be adapted later
    glTexImage2D(params.target, 0, glColorFormat, texData.width, texData.height, 0, glColorFormat,
        GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(params.target);

    stbi_image_free(data);

    log_.info("Loaded texture: %s (id:%d %dx%dx%d)", resPath.c_str(), texData.id, texData.width, texData.height,
        texData.numChannels);

    return texData;
}
} // namespace assetloaders
} // namespace gui