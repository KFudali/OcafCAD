#include "NetgenMeshEngine.hpp"

#include "MeshPreprocessor.hpp"
#include "MeshPostprocessor.hpp"
#include "MeshingLauncher.hpp"
#include "DomainRegistry.hpp"
#include "NetgenToVTK.hpp"


bool NetgenMeshEngine::generateSurfaceMesh(MeshObject& aMeshObject) const {
    auto meshInput = mMeshPre->preprocessMeshObject(aMeshObject);
    
    mMeshingLauncher->generateSurfaceMesh(meshInput);
    auto surfaceMesh = mMeshPost->postProcessSurfMesh(meshInput);
   
    // aMeshObject.setSurfaceMesh(surfaceMesh);
    
    return true;
}

bool NetgenMeshEngine::generateVolumeMesh(MeshObject& aMeshObject) const {
    if( !aMeshObject.hasSurfaceMesh() ){
        generateSurfaceMesh(aMeshObject);
    }
    auto meshInput = mMeshPre->preprocessMeshObject(aMeshObject);
    
    mMeshingLauncher->generateVolumeMesh(meshInput);
   
    auto volumeMesh = mMeshPost->postProcessVolMesh(meshInput);
    
    // aMeshObject.setVolumeMesh(volumeMesh);
    return true;
}