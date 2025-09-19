#include "STEPImporter.hpp"
#include <STEPCAFControl_Reader.hxx>
#include <XCAFApp_Application.hxx>


void STEPImporter::importIntoDoc(
    PartDocument& aDestDoc, 
    AbstractProgressScope& aProgressScope
) {
    auto occDoc = initDocument();
    transferSourceToOccDoc(mSource, occDoc, aProgressScope);
    PartDocument::(occDoc, aDestDoc)


}

Handle(TDocStd_Document) STEPImporter::initDocument() const{
    auto app = XCAFApp_Application::GetApplication();
    Handle(TDocStd_Document) document;
    app->NewDocument("XmlXCAF", document);
    return document;
}

void STEPImporter::transferSource(
    AbstractInputSource* aSource,
    Handle(TDocStd_Document) aDestDoc,
    AbstractProgressScope& aProgressScope
) const {
    std::string firstLine;
    std::getline(mSource->stream(), firstLine);
    if (firstLine.find("ISO-10303-21") == std::string::npos) {
        std::string msg = "File is missing ISO-10303-21 header";
        throw STEPImporterExceptions::CouldNotReadSTEPFile(msg);
    }
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
    OccProgressScopeWrapper progressWrapper(aProgressScope);
    reader.Transfer(aDestDoc, progressWrapper);
}