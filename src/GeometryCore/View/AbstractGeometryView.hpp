#ifndef AbstractGeometryView_hpp
#define AbstractGeometryView_hpp

#include "PartId.hpp"
#include "PartView.hpp"

class AbstractGeometryView {
    public:

    const PartView part(const PartId& aPartId) const = 0;
    std::vector<PartId> freePartsIdList() const = 0;
    std::vector<PartId> allPartsIdList() const = 0;

};

#endif
