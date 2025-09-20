#ifndef PartDocumentImport_hpp
#define PartDocumentImport_hpp

#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>
#include <optional>

#include "AbstractProgressPublisher.hpp"
#include "PartDocument.hpp"
#include "PartDocumentImporterExceptions.hpp"
class XCAFDoc_ShapeTool;
class XCAFDoc_ColorTool;

class PartDocumentImporter {
    public:
    static void import(
        Handle(TDocStd_Document) aSource, 
        PartDocument& aDest,
        AbstractProgressPublisher& aProgressPublisher
    );

    protected:
    PartDocumentImporter(
        Handle(TDocStd_Document) aSource, 
        PartDocument& aDest,
        AbstractProgressPublisher& aProgressPublisher
    ); 
    void import();

    void importLabel(TDF_Label aLabel);
    PrototypeLabel importPrototype(TDF_Label aProtoLabel);
    
    void importPart(
        TDF_Label aPartLabel, 
        std::optional<PartLabel> aDestParent = std::nullopt
    );
    PrototypeLabel importPartPrototype(TDF_Label aPartLabel);
    void importPartComponents(
        TDF_Label aSrcCompLabel, 
        PartLabel aDestParentLabel
    );


    bool isPrototype(TDF_Label aLabel) const;
    bool isAssembly(TDF_Label aLabel) const;
    bool isPart(TDF_Label aLabel) const;

    private:
    Handle(TDocStd_Document) mSrc;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
    Handle(XCAFDoc_ColorTool) mColorTool;
    PartDocument& mDest;
    AbstractProgressPublisher& mProgressScope;
};

#endif