#include "GeometryView.hpp"
#include <algorithm>

GeometryView::GeometryView(
    const PartDocument& aPartDocument
) : mPartDocument(aPartDocument){}

std::vector<PartLabel> GeometryView::topLevelPartLabels() const {
    return mPartDocument.topLevelParts();
}

std::vector<PartView> GeometryView::topLevelParts() const {
    auto partLabels = mPartDocument.topLevelParts();
    std::vector<PartView> partViews;
    partViews.reserve(partLabels.size());

    std::transform(partLabels.begin(), partLabels.end(),
        std::back_inserter(partViews),
        [](const PartLabel& label) {
            return PartView(label);
    });
    return partViews;
}


std::vector<GeometryObject> GeometryView::geometryObjects() const {
    auto partLabels = mPartDocument.topLevelParts();
    std::vector<GeometryObject> geoObjects;
    geoObjects.reserve(partLabels.size());

    std::transform(partLabels.begin(), partLabels.end(),
        std::back_inserter(geoObjects),
        [](const PartLabel& label) {
            return GeometryObject(label);
    });
    return geoObjects;
}