#include "GameObject.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gui
{
namespace objects
{
GameObject::GameObject(const mesh::Mesh& mesh)
    : mesh_(mesh)
{}

void GameObject::bind() const
{
    mesh_.bind();
}

glm::mat4 GameObject::getModelMatrix()
{
    if (!transform_.dirty)
    {
        return transform_.modelMat;
    };

    glm::mat4& modelMat = transform_.modelMat;
    modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, transform_.pos);
    modelMat = glm::rotate(modelMat, glm::radians(transform_.rot.x), glm::vec3(1, 0, 0));
    modelMat = glm::rotate(modelMat, glm::radians(transform_.rot.y), glm::vec3(0, 1, 0));
    modelMat = glm::rotate(modelMat, glm::radians(transform_.rot.z), glm::vec3(0, 0, 1));
    modelMat = glm::scale(modelMat, transform_.scale);

    return modelMat;
}
} // namespace objects
} // namespace gui