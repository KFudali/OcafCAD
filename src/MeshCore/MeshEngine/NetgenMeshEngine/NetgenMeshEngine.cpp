#include "NetgenMeshEngine.hpp"

#ifndef OCCGEOMETRY
#define OCCGEOMETRY
#endif

#include <occgeom.hpp>
#include <meshing.hpp>

bool NetgenMeshEngine::generateSurfaceMesh(const MeshObject& aMeshObject) const {
    auto shape = aMeshObject.geometry().rootShape();
    auto geometry = std::make_shared<netgen::OCCGeometry>(shape);
    auto meshPtr = std::make_shared<netgen::Mesh>();
    meshPtr->SetGeometry(geometry);
    auto params = netgen::MeshingParameters();
    geometry->GenerateMesh(meshPtr, params);
    return true;
}

bool NetgenMeshEngine::generateVolumeMesh(const MeshObject& aMeshObject) const {
    return true;
}