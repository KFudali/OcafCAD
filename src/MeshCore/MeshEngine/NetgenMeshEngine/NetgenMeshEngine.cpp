#include "NetgenMeshEngine.hpp"


#include "NetgenToVTK.hpp"
bool NetgenMeshEngine::generateSurfaceMesh(const MeshObject& aMeshObject) const {
    auto shape = aMeshObject.geometry().rootShape();
    auto geometry = std::make_shared<netgen::OCCGeometry>(shape);
    auto meshPtr = std::make_shared<netgen::Mesh>();
    meshPtr->SetGeometry(geometry);

    netgen::FaceDescriptor faceDescriptor(1, 0, 1, 6);
    meshPtr->AddFaceDescriptor(faceDescriptor);
    auto params = netgen::MeshingParameters();
    geometry->GenerateMesh(meshPtr, params);
    // NetgenToVTK::transfer(*meshPtr, aMeshObject.mesh());
    return true;
}

bool NetgenMeshEngine::generateVolumeMesh(const MeshObject& aMeshObject) const {
    return true;
}