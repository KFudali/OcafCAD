#ifndef STEPImporter_hpp
#define STEPImporter_hpp

#include "AbstractImporter.hpp"

class AbstractImporter {
    virtual void importIntoDoc(
        PartDocument& aDestDoc, 
        AbstractProgressScope& aProgressScope = IdleProgressScope()
    );
};

#endif