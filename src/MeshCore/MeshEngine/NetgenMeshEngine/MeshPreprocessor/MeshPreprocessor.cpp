#include "MeshPreprocessor.hpp"

#include "Dim.hpp"
#include "ShapeDomainDescription.hpp"

MeshInput MeshPreprocessor::preprocessMeshObject(
    MeshObject& aMeshObject
) const {
    auto domains = preprocessDomains(aMeshObject);
    auto localSettings = preprocessLocalSettings(aMeshObject);
    MeshInput input(
        aMeshObject.geometry().rootShape(), 
        domains, 
        localSettings,
        aMeshObject.globalSettings()
    );
    return input;
}

ShapeDomainDescription MeshPreprocessor::preprocessDomains(
    MeshObject& aMeshObject
) const {
    DomainRegistry domainRegistry;
    auto& selectionTool = aMeshObject.geometry().namedSelections();
    auto& subShapeTool = aMeshObject.geometry().subShapes();
    auto selections = selectionTool.selections();

    auto shapeDim = DimUtils::determineDim(aMeshObject.geometry().rootShape());
    ShapeDomainDescription domainDescription{};
    for (const auto& selection : selections) {
        auto dim = DimUtils::determineDim(selection.ids().shapeType());
        auto domainId = domainRegistry.uniqueId(dim);
        SubShapeDomain domain(domainId, dim, selection.ids().subIdVec());
        domainDescription.addDomain(domain);
    };
    return domainDescription;
}

LocalMeshSettings MeshPreprocessor::preprocessLocalSettings(
    MeshObject& aMeshObject
) const {
    return LocalMeshSettings();
}

GlobalMeshSettings MeshPreprocessor::preprocessGlobalSettings(
    MeshObject& aMeshObject
) const {
    return GlobalMeshSettings();
}