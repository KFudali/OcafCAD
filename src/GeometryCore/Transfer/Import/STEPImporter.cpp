#include "STEPImporter.hpp"
#include <STEPCAFControl_Reader.hxx>
#include <XCAFApp_Application.hxx>

#include "GeometryDocImporter.hpp"
#include "OccProgressIndicator.hpp"


void STEPImporter::importIntoDoc(
    DocumentGeometry& aDestDoc, 
    AbstractProgressPublisher& aProgressPublisher
) {
    auto occDoc = initDocument();
    transferSource(occDoc, aProgressPublisher);
    GeometryDocImporter::import(occDoc, aDestDoc, aProgressPublisher);
}

Handle(TDocStd_Document) STEPImporter::initDocument() const{
    auto app = XCAFApp_Application::GetApplication();
    Handle(TDocStd_Document) document;
    app->NewDocument("XmlXCAF", document);
    return document;
}

void STEPImporter::transferSource(
    Handle(TDocStd_Document) aDestDoc,
    AbstractProgressPublisher& aProgressPublisher
) const {
    STEPCAFControl_Reader reader;
    reader.SetColorMode(true);
    reader.SetNameMode(true);

    IFSelect_ReturnStatus result = reader.ReadStream(
        mSource->name().c_str(), 
        mSource->stream()
    );

    if (result != IFSelect_RetDone) {
        throw STEPImporterExceptions::CouldNotReadSTEPFile(
            "CAF reader did not return Done"
        );
    }
    OccProgressIndicator progressIndicator(aProgressPublisher);
    reader.Transfer(aDestDoc, progressIndicator.Start());
}