#ifndef GeometryView_hpp
#define GeometryView_hpp

#include "PartView.hpp"
#include "PartDocument.hpp"
#include "GeometryObject.hpp"

class GeometryView {
    public:

    GeometryView(const PartDocument& aPartDocument);

    std::vector<PartLabel> topLevelPartLabels() const;
    std::vector<PartView> topLevelParts() const;
    std::vector<GeometryObject> geometryObjects() const;

    private:
    const PartDocument& mPartDocument;
};

#endif
