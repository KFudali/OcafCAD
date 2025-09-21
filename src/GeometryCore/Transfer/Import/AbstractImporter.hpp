#ifndef AbstractImporter_hpp
#define AbstractImporter_hpp

#include "PartDocument.hpp"
#include "AbstractProgressPublisher.hpp"

class AbstractImporter{
    public:
    virtual void importIntoDoc(
        PartDocument& aDestDoc,
        AbstractProgressPublisher& aProgressPublisher
    ) = 0;
};

#endif