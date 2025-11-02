#ifndef GeometryView_hpp
#define GeometryView_hpp

#include "DocumentGeometry.hpp"
#include "GeometryObject.hpp"
#include "Part.hpp"

class GeometryView {
    public:

    GeometryView(const DocumentGeometry& aDocumentGeometry);

    std::vector<PartLabel> topLevelPartLabels() const;
    std::vector<Part> topLevelParts() const;
    std::vector<GeometryObject> geometryObjects() const;

    private:
    const DocumentGeometry& mDocumentGeometry;
};

#endif
