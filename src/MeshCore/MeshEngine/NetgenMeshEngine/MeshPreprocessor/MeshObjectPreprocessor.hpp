#ifndef MeshObjectPreprocessor_hpp
#define MeshObjectPreprocessor_hpp

#include "MeshInput.hpp"
#include "MeshObject.hpp"
#include "DomainRegistry.hpp"

class MeshObjectPreprocessor {
    public:
    MeshObjectPreprocessor() = default;

    // MeshInput preprocessMeshObject(const MeshObject& aMeshObject);
   
    private: 
    DomainRegistry mDomains;
};

#endif