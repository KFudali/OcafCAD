#include "MeshPreprocessor.hpp"

#include "Dim.hpp"
#include "ShapeDomainDescription.hpp"

MeshInput MeshPreprocessor::preprocessMeshObject(
    MeshObject& aMeshObject
) {
    auto domains = preprocessDomains(aMeshObject);
    auto settings = preprocessLocalSettings(aMeshObject);
    MeshInput input(aMeshObject.geometry().rootShape(), domains, settings);
    return input;
}

ShapeDomainDescription MeshPreprocessor::preprocessDomains(
    MeshObject& aMeshObject
) {
    auto& selectionTool = aMeshObject.geometry().namedSelections();
    auto& subShapeTool = aMeshObject.geometry().subShapes();
    auto selections = selectionTool.selections();

    auto shapeDim = DimUtils::determineDim(aMeshObject.geometry().rootShape());
    auto shapeId = mDomainRegistry.uniqueId(shapeDim);
    ShapeDomainDescription domainDescription{};
    for (const auto& selection : selections) {
        auto dim = DimUtils::determineDim(selection.ids().shapeType());
        auto domainId = mDomainRegistry.uniqueId(dim);
        SubShapeDomain domain(domainId, dim, selection.ids().subIdVec());
        domainDescription.addDomain(domain);
    };
    return domainDescription;
}

LocalMeshSettings MeshPreprocessor::preprocessLocalSettings(
    MeshObject& aMeshObject
) {
    return LocalMeshSettings();
}