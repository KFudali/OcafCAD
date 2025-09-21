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
        std::shared_ptr<AbstractInputSource> aSource
    ) : mSource(aSource) {}

    void importIntoDoc(
        PartDocument& aDestDoc, 
        AbstractProgressPublisher& aProgressPublisher
    ) override;
    
    private:
    Handle(TDocStd_Document) initDocument() const;
    void transferSource(
        Handle(TDocStd_Document) aDestDoc,
        AbstractProgressPublisher& aProgressPublisher
    ) const;

    std::shared_ptr<AbstractInputSource> mSource;
};

#endif