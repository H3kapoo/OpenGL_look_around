#pragma once

#include <string>
#include <unordered_map>

#include <GL/glew.h>

#include "src/tools/Logger.hpp"
#include "src/common/Texture.hpp"

namespace gui
{
namespace assetloaders
{
class TextureLoader
{
public:
    static TextureLoader& get();
    common::Texture loadTexture(const std::string& resPath,
        const common::Texture::Params& params = common::Texture::Params{});

private:
    TextureLoader();
    TextureLoader(const TextureLoader&);
    TextureLoader& operator=(const TextureLoader&);
    TextureLoader(TextureLoader&&);
    TextureLoader& operator=(TextureLoader&&);

    common::Texture loadInternal(const std::string& resPath,
        const common::Texture::Params& params);

private:
    tools::Logger log_;
    std::unordered_map<std::string, common::Texture> pathToTexIdMap_;
};
} // namespace assetloaders
} // namespace gui