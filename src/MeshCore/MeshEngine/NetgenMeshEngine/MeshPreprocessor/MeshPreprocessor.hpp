#ifndef MeshPreprocessor_hpp
#define MeshPreprocessor_hpp

#include "MeshInput.hpp"
#include "MeshObject.hpp"
#include "DomainRegistry.hpp"
#include "ShapeDomainDescription.hpp"
#include "LocalMeshSettings.hpp"

class MeshPreprocessor {
    public:
    MeshPreprocessor() = default;

    MeshInput preprocessMeshObject(MeshObject& aMeshObject);
   
    private: 
    ShapeDomainDescription preprocessDomains(MeshObject& aMeshObject);
    LocalMeshSettings preprocessLocalSettings(MeshObject& aMeshObject);

    DomainRegistry mDomainRegistry;
};

#endif