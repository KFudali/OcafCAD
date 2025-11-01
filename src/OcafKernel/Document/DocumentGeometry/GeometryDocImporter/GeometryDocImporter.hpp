#ifndef GeometryDocImporter_hpp
#define GeometryDocImporter_hpp

#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>
#include <optional>

#include "DocumentGeometry.hpp"
#include "AbstractProgressPublisher.hpp"
#include "GeometryDocImportExceptions.hpp"

class XCAFDoc_ShapeTool;
class XCAFDoc_ColorTool;

class GeometryDocImporter {
    public:
    static void import(
        Handle(TDocStd_Document) aSource, 
        DocumentGeometry& aDest,
        AbstractProgressPublisher& aProgressPublisher
    );

    protected:
    GeometryDocImporter(
        Handle(TDocStd_Document) aSource, 
        DocumentGeometry& aDest,
        AbstractProgressPublisher& aProgressPublisher
    ); 
    void import();

    void importLabel(TDF_Label aLabel);
    ShapeLabel importPrototype(TDF_Label aProtoLabel);
    
    void importPrototypeAsPart(
        TDF_Label aProtoLabel
    );
    void importPart(
        TDF_Label aPartLabel, 
        std::optional<PartLabel> aDestParent = std::nullopt
    );

    ShapeLabel importPartPrototype(TDF_Label aPartLabel);
    ShapeLabel importAssemblyPrototype(TDF_Label aAssemblyLabel);

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
    DocumentGeometry& mDest;
    AbstractProgressPublisher& mProgressScope;
};

#endif