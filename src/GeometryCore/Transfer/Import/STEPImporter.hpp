#ifndef STEPImporter_hpp
#define STEPImporter_hpp

#include "AbstractInputSource.hpp"
#include "AbstractImporter.hpp"
#include "STEPImporterExceptions.hpp"
#include <string>
#include <memory>

#include <Standard_Handle.hxx>
class TDocStd_Document;
class STEPImporter : public AbstractImporter {
    public:
    STEPImporter(
        std::unique_ptr<AbstractInputSource> aSource
    ) : mSource(std::move(aSource)) {}

    void importIntoDoc(
        PartDocument& aDestDoc, 
        AbstractProgressScope& aProgressScope
    ) override;
   
    
    private:
    Handle(TDocStd_Document) initDocument() const;
    Handle(TDocStd_Document) readSource(AbstractInputSource* aSource) const;
    std::unique_ptr<AbstractInputSource> mSource;
};

#endif