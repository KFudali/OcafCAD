#ifndef STEPImporter_hpp
#define STEPImporter_hpp

#include "AbstractImporter.hpp"

class STEPImporter : public AbstractImporter {
    void importIntoDoc(
        PartDocument& aDestDoc, 
        AbstractProgressScope& aProgressScope
    ) override;
};

#endif