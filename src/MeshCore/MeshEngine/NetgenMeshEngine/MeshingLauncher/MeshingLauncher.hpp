#ifndef MeshingLauncher_hpp
#define MeshingLauncher_hpp

#include <memory>
#include "MeshInput.hpp"

class MeshingLauncher {
    public:
    
    MeshingLauncher() = default;
    
    bool generateSurfaceMesh(MeshInput& aMeshInput);
    bool generateVolumeMesh(MeshInput& aMeshInput);
};


#endif
