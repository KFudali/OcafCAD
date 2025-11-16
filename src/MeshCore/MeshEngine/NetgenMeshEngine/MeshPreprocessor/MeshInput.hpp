#ifndef MeshInput_hpp
#define MeshInput_hpp

#include "MeshObject.hpp"
#include "DomainId.hpp"
#include "Shape.hpp"
#include "ShapeDomainDescription.hpp"
#include "LocalMeshSettings.hpp"

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
        const LocalMeshSettings& aLocalSettings
    );
    inline const ShapeDomainDescription& domains() const {return mDomains;}
    
    inline netgen::Mesh& mesh() {return *mNetgenMesh;}
    inline netgen::OCCGeometry& geometry() {return *mNetgenGeometry;}

    private:
    
    static std::shared_ptr<netgen::Mesh> makeMesh(
        const std::shared_ptr<netgen::OCCGeometry>& geometry
    ) {
        auto mesh = std::make_shared<netgen::Mesh>();
        mesh->SetGeometry(geometry);
        return mesh;
    }

private:
    std::shared_ptr<netgen::OCCGeometry> mNetgenGeometry;
    std::shared_ptr<netgen::Mesh> mNetgenMesh;
    const ShapeDomainDescription mDomains;
    Dim mDim;
};

#endif