#ifndef AbstractImporter_hpp
#define AbstractImporter_hpp

#include "PartDocument.hpp"
#include "AbstractProgressScope.hpp"

class AbstractImporter{
    virtual void importIntoDoc(
        PartDocument& aDestDoc,
        AbstractProgressScope& aProgressScope
    ) = 0;
};

#endif