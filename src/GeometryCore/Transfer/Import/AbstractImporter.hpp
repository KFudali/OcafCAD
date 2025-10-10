#ifndef AbstractImporter_hpp
#define AbstractImporter_hpp

#include "DocumentGeometry.hpp"
#include "AbstractProgressPublisher.hpp"

class AbstractImporter{
    public:
    virtual void importIntoDoc(
        DocumentGeometry& aDestDoc,
        AbstractProgressPublisher& aProgressPublisher
    ) = 0;
};

#endif