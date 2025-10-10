#include "GeometryView.hpp"
#include <algorithm>

GeometryView::GeometryView(
    const DocumentGeometry& aDocumentGeometry
) : mDocumentGeometry(aDocumentGeometry){}

std::vector<PartLabel> GeometryView::topLevelPartLabels() const {
    return mDocumentGeometry.topLevelParts();
}

std::vector<GeometryPart> GeometryView::topLevelParts() const {
    auto partLabels = mDocumentGeometry.topLevelParts();
    std::vector<GeometryPart> geometryParts;
    geometryParts.reserve(partLabels.size());

    std::transform(partLabels.begin(), partLabels.end(),
        std::back_inserter(geometryParts),
        [](const PartLabel& label) {
            return GeometryPart(label);
    });
    return geometryParts;
}


std::vector<GeometryObject> GeometryView::geometryObjects() const {
    auto partLabels = mDocumentGeometry.topLevelParts();
    std::vector<GeometryObject> geoObjects;
    geoObjects.reserve(partLabels.size());

    std::transform(partLabels.begin(), partLabels.end(),
        std::back_inserter(geoObjects),
        [](const PartLabel& label) {
            return GeometryObject(label);
    });
    return geoObjects;
}