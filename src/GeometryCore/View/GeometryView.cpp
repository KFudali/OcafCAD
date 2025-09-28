#include "GeometryView.hpp"

GeometryView::GeometryView(
    const PartDocument& aPartDocument
) : mPartDocument(aPartDocument){}

std::vector<PartLabel> GeometryView::topLevelPartLabels() const {
    return std::vector<PartLabel>{};
}

std::vector<PartView> GeometryView::topLevelParts() const {
    return std::vector<PartView>{};
}

std::vector<GeometryObject> GeometryView::geometryObjects() const {
    return std::vector<GeometryObject> {};
}