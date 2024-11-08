#pragma once

#include <vector>
#include <cstdint>

#include <GL/glew.h>

#include "src/tools/Logger.hpp"

namespace gui
{
namespace mesh
{
class Mesh
{
public:
    enum BufferType : uint8_t
    {
        STATIC,
        DYNAMIC,
        STREAM
    };

private:
    struct Layer
    {
        std::string name;
        uint32_t index{0};
        uint32_t count{0};
    };

public:
    Mesh();
    ~Mesh();

    void setDataBuffer(std::vector<float>&& data, const BufferType drawType = Mesh::STATIC);
    void setElementBuffer(std::vector<uint32_t>&& data, const BufferType drawType = Mesh::STATIC);
    void addVertexLayer(const uint32_t vertexAttribIndex, const uint32_t dataTypeCount,
        const std::string& layerName);
    void buildLayers();

    void bind() const;
    void unbind() const;

private:
    std::string convertDrawTypeToString(const BufferType drawType) const;
    uint32_t convertDrawType(const BufferType drawType) const;

private:
    uint32_t vaoId_{0};
    uint32_t vboId_{0};
    uint32_t eboId_{0};

    // Store data as we might wanna look into it later. Can be removed if really not needed.
    std::vector<float> vertexData_;
    std::vector<uint32_t> elementData_;
    std::vector<Layer> layers_;

    tools::Logger log_;
};
} // namespace mesh
} // namespace gui