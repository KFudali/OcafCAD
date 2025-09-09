#ifndef AbstractImporter_hpp
#define AbstractImporter_hpp

#include "PartDocument.hpp"
#include "AbstractProgressScope.hpp"
#include "IdleProgressScope.hpp"

class AbstractImporter{
    virtual void importIntoDoc(
        PartDocument& aDestDoc,
        AbstractProgressScope& aProgressScope = IdleProgressScope()
    ) = 0;
};

#endif