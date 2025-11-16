#ifndef MeshPostprocessor_hpp
#define MeshPostprocessor_hpp

#include <memory>

#include "MeshInput.hpp"
#include "SurfaceMesh.hpp"
#include "VolumeMesh.hpp"

class MeshPostprocessor {
    public:
    MeshPostprocessor() = default;

    std::unique_ptr<SurfaceMesh> postProcessSurfMesh(const MeshInput& aMeshInput);
    std::unique_ptr<VolumeMesh> postProcessVolMesh(const MeshInput& aMeshInput);
    
    private:
};

#endif