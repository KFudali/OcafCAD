#include "NetgenMeshEngine.hpp"

#include "MeshPreprocessor.hpp"
#include "MeshPostprocessor.hpp"
#include "MeshingLauncher.hpp"
#include "DomainRegistry.hpp"
#include "NetgenToVTK.hpp"


bool NetgenMeshEngine::generateSurfaceMesh(MeshObject& aMeshObject) const {
    auto meshInput = mMeshPre->preprocessMeshObject(aMeshObject);
    
    mMeshingLauncher->generateSurfaceMesh(meshInput);

    mMeshPost->transferSurfaceMesh(meshInput, aMeshObject);
    
    return true;
}

bool NetgenMeshEngine::generateVolumeMesh(MeshObject& aMeshObject) const {
    if( !aMeshObject.hasSurfaceMesh() ){
        generateSurfaceMesh(aMeshObject);
    }
    auto meshInput = mMeshPre->preprocessMeshObject(aMeshObject);
    
    mMeshingLauncher->generateVolumeMesh(meshInput);

    mMeshPost->transferVolumeMesh(meshInput, aMeshObject);
    
    return true;
}