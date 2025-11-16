#include "MeshInput.hpp"

MeshInput::MeshInput(
    const Shape& aShape,
    const ShapeDomainDescription& aDomainDescription,
    const LocalMeshSettings& aLocalSettings
) : mNetgenGeometry(std::make_shared<netgen::OCCGeometry>(aShape)),
    mNetgenMesh(makeMesh(mNetgenGeometry)),
    mDomains(aDomainDescription),
    mDim(DimUtils::determineDim(aShape)){}