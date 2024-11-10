#include "src/renderer/Renderer.hpp"

#include <GL/glew.h>

namespace gui
{
namespace renderer
{
void Renderer::renderElements(const RenderPrimitive prim, const uint64_t vertIndexCount,
        const uint64_t offset)
{
    glDrawElements(prim, vertIndexCount, GL_UNSIGNED_INT, (void*)offset);
}
} // namespace gui
} // namespace renderer