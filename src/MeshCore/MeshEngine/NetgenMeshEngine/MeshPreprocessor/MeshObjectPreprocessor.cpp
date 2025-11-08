#include "MeshObjectPreprocessor.hpp"

#include "Dim.hpp"

void applyNamedSelections(
    MeshInput& aMeshInput, 
    const std::vector<NamedSelection>& aNamedSelections
) {
    aMeshInput.applyNamedSelection();
}

// MeshInput MeshObjectPreprocessor::preprocessMeshObject(
//     const MeshObject& aMeshObject
// ) {
    // auto objectShape& = aMeshObject.geometry().rootShape();
    // auto objectDim = DimUtils::determineDim(objectShape);
    // auto domain = mDomains.getFreeDomainId(objectDim);
    // MeshInput input(objectShape, domain);
   
    // auto namedSelections& = aMeshObject.geometry().namedSelections().namedSelections();
    // applyNamedSelection(input, namedSelections); 

    // auto localSettings& = aMeshObject.localSettings();
    // applyLocalSettings(input, localSettings); 

    // auto globalSettings& = aMeshObject.localSettings();
    // applyGlobalSettings(input, globalSettings); 
// }