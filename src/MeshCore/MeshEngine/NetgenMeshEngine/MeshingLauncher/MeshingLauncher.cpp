#include "MeshingLauncher.hpp"

bool MeshingLauncher::generateSurfaceMesh(
    MeshInput& aMeshInput
) {
    aMeshInput.geometry().MeshSurface(
        aMeshInput.mesh(),
        aMeshInput.meshingParams()
    );
    return true;
}

bool MeshingLauncher::generateVolumeMesh(
    MeshInput& aMeshInput
) {
    auto result = aMeshInput.geometry().GenerateMesh(
        aMeshInput.meshPtr(),
        aMeshInput.meshingParams()
    );
    if (result == 0) {
        return true;
    } else {
        return false;
    }
}