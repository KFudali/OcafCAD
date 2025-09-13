#include "STEPImporter.hpp"
#include "STEPCAFControl_Reader.hxx"


void STEPImporter::importIntoDoc(
    PartDocument& aDestDoc, 
    AbstractProgressScope& aProgressScope
) {
    
}

Handle(TDocStd_Document) STEPImporter::readSource(AbstractInputSource* aSource) const {
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

    auto document = initDocument();
    reader.Transfer(document, progressIndicator.Start());
    return document
}