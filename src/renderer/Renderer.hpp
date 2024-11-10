#pragma once

#include <cstdint>

#include <GL/glew.h>

namespace gui
{
namespace renderer
{
using RenderPrimitive = uint32_t;

class Renderer
{
public:
    static void renderElements(const RenderPrimitive prim = GL_TRIANGLES,
        const uint64_t vertIndexCount = 6, const uint64_t offset = 0);

private:
    Renderer();
    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);
    Renderer(Renderer&&);
    Renderer& operator=(Renderer&&);
};
} // namespace gui
} // namespace renderer