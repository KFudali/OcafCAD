#ifndef GeometryView_hpp
#define GeometryView_hpp

#include "DocumentGeometry.hpp"
#include "GeometryObject.hpp"
#include "GeometryPart.hpp"

class GeometryView {
    public:

    GeometryView(const DocumentGeometry& aDocumentGeometry);

    std::vector<PartLabel> topLevelPartLabels() const;
    std::vector<GeometryPart> topLevelParts() const;
    std::vector<GeometryObject> geometryObjects() const;

    private:
    const DocumentGeometry& mDocumentGeometry;
};

#endif
