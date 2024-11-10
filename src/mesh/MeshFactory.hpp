#pragma once

#include "src/mesh/Mesh.hpp"

namespace gui
{
namespace mesh
{
class MeshFactory
{
public:
    static Mesh createRectMesh();
    static Mesh createCubeMesh();

private:
    MeshFactory();
    MeshFactory(const MeshFactory&);
    MeshFactory& operator=(const MeshFactory&);
    MeshFactory(MeshFactory&&);
    MeshFactory& operator=(MeshFactory&&);
};
} // namespace mesh
} // namespace gui