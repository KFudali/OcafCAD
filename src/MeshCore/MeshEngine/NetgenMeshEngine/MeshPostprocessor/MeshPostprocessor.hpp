#ifndef MeshPostprocessor_hpp
#define MeshPostprocessor_hpp

#include <memory>

#include "MeshInput.hpp"

class MeshPostprocessor {
    public:
    MeshPostprocessor() = default;

    bool transferSurfaceMesh(
        const MeshInput& aMeshInput,
        MeshObject& aMeshObject
    ) const {return true;}
    
    bool transferVolumeMesh(
        const MeshInput& aMeshInput,
        MeshObject& aMeshObject
    ) const {return true;}
    
    private:
    


};

#endif