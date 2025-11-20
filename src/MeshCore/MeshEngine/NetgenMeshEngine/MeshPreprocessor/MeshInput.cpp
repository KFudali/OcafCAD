#include "MeshInput.hpp"

MeshInput::MeshInput(
    const Shape& aShape,
    const ShapeDomainDescription& aDomainDescription,
    const LocalMeshSettings& aLocalSettings,
    const GlobalMeshSettings& aGlobalSettings
) : mNetgenGeometry(std::make_shared<netgen::OCCGeometry>(aShape)),
    mNetgenMesh(makeMesh(mNetgenGeometry)),
    mNetgenMeshingParams(makeNetgenMeshingParams(aGlobalSettings)),
    mDomains(aDomainDescription),
    mDim(DimUtils::determineDim(aShape)),
    mLocalSettings(aLocalSettings),
    mGlobalSettings(aGlobalSettings){}

netgen::MeshingParameters makeNetgenMeshingParams(
    const GlobalMeshSettings& aMeshSettings
){
    return netgen::MeshingParameters();
}