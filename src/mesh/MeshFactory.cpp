#include "MeshFactory.hpp"

#include "src/tools/Logger.hpp"

namespace gui
{
namespace mesh
{
Mesh MeshFactory::createRectMesh()
{
    tools::Logger log_{"MeshFactory"};
    log_.debug(__func__);

    std::vector<float> vertices = {
         // positions        // texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top left 
    };

    std::vector<uint32_t> indices = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Mesh mesh;
    mesh.setDataBuffer(std::move(vertices), Mesh::STATIC);
    mesh.setElementBuffer(std::move(indices), Mesh::STATIC);
    mesh.addVertexLayer(0, 3, "Position");
    mesh.addVertexLayer(1, 2, "TextureUV");
    // mesh.addVertexLayer(2, 3, "ColorRGB");
    mesh.buildLayers();

    // This should take advantage of RVO
    return mesh;
}

Mesh MeshFactory::createCubeMesh()
{
    tools::Logger log_{"MeshFactory"};
    log_.debug(__func__);

    // Vertex duplication inevitable if we want per quad UVs
    std::vector<float> vertices = {
         // positions         // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f 
    };

    std::vector<uint32_t> indices = {  
        0,   1, 2,    2,  3,  0, // back face
        4,   5, 6,    6,  7,  4, // front face
        8,   9, 10,  10, 11,  8, // left face
        12, 13, 14,  14, 15, 12, // right face
        16, 17, 18,  18, 19, 16, // bottom face
        20, 21, 22,  22, 23, 20  // top face
    };

    Mesh mesh;
    mesh.setDataBuffer(std::move(vertices), Mesh::STATIC);
    mesh.setElementBuffer(std::move(indices), Mesh::STATIC);
    mesh.addVertexLayer(0, 3, "Position");
    mesh.addVertexLayer(1, 2, "TextureUV");
    mesh.buildLayers();

    // This should take advantage of RVO
    return mesh;
}
} // namespace mesh
} // namespace gui