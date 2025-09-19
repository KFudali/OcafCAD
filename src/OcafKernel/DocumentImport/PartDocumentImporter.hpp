#ifndef PartDocumentImport_hpp
#define PartDocumentImport_hpp

#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>

#include "AbstractProgressScope.hpp"
#include "PartDocument.hpp"
#include "PartDocumentImporterExceptions.hpp"
class XCAFDoc_ShapeTool;
class XCAFDoc_ColorTool;

class PartDocumentImporter {
    public:
    static void import(
        Handle(TDocStd_Document) aSource, 
        PartDocument& aDest,
        AbstractProgressScope& aProgressScope
    );

    protected:
    PartDocumentImporter(
        Handle(TDocStd_Document) aSource, 
        PartDocument& aDest,
        AbstractProgressScope& aProgressScope
    ); 
    void import();

    void importLabel(TDF_Label aLabel);
    PrototypeLabel importPrototype(TDF_Label aProtoLabel);
    void importComponent(
        TDF_Label aCompLabel,
        PartLabel aParentAssembly
    );
    PartLabel importPart(TDF_Label aPartLabel);
    PartLabel importAssembly(TDF_Label aAssemblyLabel);

    bool isPrototype(TDF_Label aLabel) const;
    bool isAssembly(TDF_Label aLabel) const;
    bool isPart(TDF_Label aLabel) const;

    private:
    Handle(TDocStd_Document) mSrc;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
    Handle(XCAFDoc_ColorTool) mColorTool;
    PartDocument& mDest;
    AbstractProgressScope& mProgressScope;
};

#endif