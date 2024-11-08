#pragma once

#include "src/tools/Logger.hpp"
#include <GL/glew.h>

namespace gui
{
namespace debug
{
class Debug
{
public:
    static Debug& get();

    void enableWireframe();
    void disableWireframe();
private:
    Debug();
    Debug(const Debug&);
    Debug& operator=(const Debug&);

    static void debugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, 
        const char *message, const void *userParam);

private:
    tools::Logger log_;
};
} // namespace debug
} // namespace gui