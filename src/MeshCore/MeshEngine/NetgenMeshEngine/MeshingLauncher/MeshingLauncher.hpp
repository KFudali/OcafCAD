#ifndef MeshingLauncher_hpp
#define MeshingLauncher_hpp

#include <memory>
#include "SurfaceMesh.hpp"
#include "VolumeMesh.hpp"
#include "MeshInput.hpp"

class MeshingLauncher {
    public:
    
    MeshingLauncher() = default;
    
    std::unique_ptr<SurfaceMesh> generateSurfaceMesh(const MeshInput& aMeshInput);
    std::unique_ptr<VolumeMesh> generateVolumeMesh(const MeshInput& aMeshInput);
};


#endif
