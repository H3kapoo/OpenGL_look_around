#pragma once

#include <glm/glm.hpp>

namespace gui
{
namespace common
{
struct Transform
{
    glm::vec3 pos{0.0f};
    glm::vec3 scale{0.0f};
    glm::vec3 rot{0.0f};

    glm::mat4 modelMat{1.0f};
    bool dirty{true};
};
} // namespace common
} // namespace gui