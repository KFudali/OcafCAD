#ifndef MeshInput_hpp
#define MeshInput_hpp

#include "MeshObject.hpp"
#include "DomainId.hpp"

#ifndef OCCGEOMETRY
#define OCCGEOMETRY
#endif

#include <occgeom.hpp>
#include <meshing.hpp>
#include <memory>

class MeshInput {
public:
    MeshInput(const Shape& aShape, const DomainId& aDomainId)
        : mNetgenGeometry(std::make_shared<netgen::OCCGeometry>(aShape)),
          mNetgenMesh(makeMesh(mNetgenGeometry)),
          mId(aDomainId),
          mDim(DimUtils::determineDim(aShape)){
    }
    bool applyNamedSelection();
    // bool applyFaceSizings();
    // bool applyEdgeSizings();
    // bool applyVolumeSizings();
    // bool applyGlobalSettings();

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

    

    DomainId mId;
    Dim mDim;
};

#endif