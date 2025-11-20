#ifndef MeshInput_hpp
#define MeshInput_hpp

#include "MeshObject.hpp"
#include "DomainId.hpp"
#include "Shape.hpp"
#include "ShapeDomainDescription.hpp"
#include "LocalMeshSettings.hpp"
#include "GlobalMeshSettings.hpp"

#ifndef OCCGEOMETRY
#define OCCGEOMETRY
#endif

#include <occgeom.hpp>
#include <meshing.hpp>
#include <memory>

class MeshInput {
public:
    MeshInput(
        const Shape& aShape,
        const ShapeDomainDescription& aDomainDescription,
        const LocalMeshSettings& aLocalSettings,
        const GlobalMeshSettings& aGlobalSettings 
    );
    inline const ShapeDomainDescription& domains() const {return mDomains;}
    
    inline netgen::Mesh& mesh() {return *mNetgenMesh;}
    inline std::shared_ptr<netgen::Mesh>& meshPtr() {return mNetgenMesh;}
    inline netgen::OCCGeometry& geometry() {return *mNetgenGeometry;}
    
    inline netgen::MeshingParameters& meshingParams() {
        return mNetgenMeshingParams;
    }
    
    private:
    static std::shared_ptr<netgen::Mesh> makeMesh(
        const std::shared_ptr<netgen::OCCGeometry>& geometry
    ) {
        auto mesh = std::make_shared<netgen::Mesh>();
        mesh->SetGeometry(geometry);
        return mesh;
    }

    static netgen::MeshingParameters makeNetgenMeshingParams(
        const GlobalMeshSettings& meshSettings
    );


private:
    std::shared_ptr<netgen::OCCGeometry> mNetgenGeometry;
    std::shared_ptr<netgen::Mesh> mNetgenMesh;
    netgen::MeshingParameters mNetgenMeshingParams;

    const ShapeDomainDescription mDomains;
    const Dim mDim;
    const LocalMeshSettings mLocalSettings;
    const GlobalMeshSettings mGlobalSettings;
};

#endif