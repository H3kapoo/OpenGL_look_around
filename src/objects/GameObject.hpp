#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "src/common/Transform.hpp"
#include "src/mesh/Mesh.hpp"
#include "src/shader/Shader.hpp"

namespace gui
{
namespace objects
{
class GameObject
{
public:
    GameObject(const mesh::Mesh& mesh);

    void bind() const;

    inline common::Transform& getTransform() { return transform_; }
    glm::mat4 getModelMatrix();

private:
    common::Transform transform_;
    mesh::Mesh mesh_;
};
} // namespace objects
} // namespace gui