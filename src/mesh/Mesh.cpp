#include "Mesh.hpp"

#include <algorithm>

namespace gui
{
namespace mesh
{

Mesh::Mesh()
    : log_("Mesh (0)")
{
    glGenVertexArrays(1, &vaoId_);
    bind();

    log_ = tools::Logger("Mesh (" + std::to_string(vaoId_) +")");

    log_.info("Created!");
}

Mesh::~Mesh()
{
    log_.info("Destroying mesh..");
    glDeleteVertexArrays(1, &vaoId_);
    glDeleteBuffers(1, &vboId_);
    glDeleteBuffers(1, &eboId_);
}

void Mesh::setDataBuffer(std::vector<float>&& data, const BufferType drawType)
{
    log_.debug("Requested %s vertex buffer", convertDrawTypeToString(drawType).c_str());

    vertexData_ = std::move(data);
    glGenBuffers(1, &vboId_);
    glBindBuffer(GL_ARRAY_BUFFER,  vboId_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData_.size(), vertexData_.data(),
        convertDrawType(drawType));
}

void Mesh::setElementBuffer(std::vector<uint32_t>&& data, const BufferType drawType)
{
    log_.debug("Requested %s element buffer", convertDrawTypeToString(drawType).c_str());

    elementData_ = std::move(data);
    glGenBuffers(1, &eboId_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(float) * elementData_.size(), elementData_.data(),
        convertDrawType(drawType));
}

void Mesh::addVertexLayer(const uint32_t vertexAttribIndex, const uint32_t dataTypeCount,
    const std::string& layerName)
{
    layers_.emplace_back(Layer{layerName, vertexAttribIndex, dataTypeCount});
}

void Mesh::buildLayers()
{
    std::sort(layers_.begin(), layers_.end(), [](const Layer& lhs, const Layer& rhs)
    {
        return lhs.index < rhs.index;
    });

    uint32_t stride{0};
    for (const auto& layer : layers_)
    {
        stride += layer.count;
    }
    stride *=  sizeof(float);

    uint64_t offset{0};
    for (const auto& layer : layers_)
    {
        log_.debug("Layer %d: %-20s | Size %2d | Offset %3ldb | Stride %ldb", layer.index, layer.name.c_str(),
            layer.count, offset, stride);
        glVertexAttribPointer(layer.index, layer.count, GL_FLOAT, false, stride, (void*)offset);
        glEnableVertexAttribArray(layer.index);
        offset += layer.count * sizeof(float);
    }
}

uint32_t Mesh::convertDrawType(const BufferType drawType) const
{
    switch (drawType)
    {
        case BufferType::STATIC:
            return GL_STATIC_DRAW;
        case BufferType::DYNAMIC:
            return GL_DYNAMIC_DRAW;
        case BufferType::STREAM:
            return GL_STREAM_DRAW;
    }

    log_.error("Invalid draw type value: %d", drawType);
    return 0;
}

std::string Mesh::convertDrawTypeToString(const BufferType drawType) const
{
    switch (drawType)
    {
        case BufferType::STATIC:
            return "Static";
        case BufferType::DYNAMIC:
            return "Dynamic";
        case BufferType::STREAM:
            return "Stream";
    }

    return "Unknown";
}

void Mesh::bind() const
{
   glBindVertexArray(vaoId_);
}

void Mesh::unbind() const
{
   glBindVertexArray(0);
}
} // namespace mesh
} // namespace gui