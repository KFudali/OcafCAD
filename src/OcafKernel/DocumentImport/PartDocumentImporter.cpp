#include "PartDocumentImporter.hpp"

#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <TDF_LabelSequence.hxx>
#include "DocLabel.hpp"

void PartDocumentImporter::import(
    Handle(TDocStd_Document) aSrc, 
    PartDocument& aDest,
    AbstractProgressPublisher& aProgressPublisher
){
    PartDocumentImporter importer(aSrc, aDest, aProgressPublisher);
    importer.import();
}

PartDocumentImporter::PartDocumentImporter(
    Handle(TDocStd_Document) aSource,
    PartDocument& aDest,
    AbstractProgressPublisher& aProgressPublisher
) : mSrc(aSource), 
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aSource->Main())),
    mColorTool(XCAFDoc_DocumentTool::ColorTool(aSource->Main())),
    mDest(aDest), 
    mProgressScope(aProgressPublisher) {}

void PartDocumentImporter::import() {
    TDF_LabelSequence topLevelLabels;
    mShapeTool->GetShapes(topLevelLabels);
    for (auto label : topLevelLabels) {
        try {
            importLabel(label);
        } catch(const PartDocumentImporterExceptions::CouldNotReadLabel& e) {
            std::cerr 
                << "Skipping label: " << DocLabel(label).toString()
                << " Reason: " << e.what() << "\n";
        }
    }
}

void PartDocumentImporter::importLabel(TDF_Label aLabel) {
    if (aLabel.IsNull() ){
        throw PartDocumentImporterExceptions::CouldNotReadLabel(
            "Trying to import NULL label."
        );
    }
    if (isPrototype(aLabel)){
        importPrototype(aLabel);
        return;
    } else {
        importPart(aLabel);
        return;
    }
    throw PartDocumentImporterExceptions::CouldNotReadLabel(
        "Label fails both isPart and isPrototype"
    );
}

bool PartDocumentImporter::isPrototype(TDF_Label aLabel) const {
    if (mShapeTool->IsReference(aLabel))
        return false;
    TopoDS_Shape shape = mShapeTool->GetShape(aLabel);
    if (shape.IsNull())
        return false;
    if (!mShapeTool->IsTopLevel(aLabel)){
        return false;
    }
    if (mShapeTool->IsAssembly(aLabel)){
        return false;
    }
    return true;
}

bool PartDocumentImporter::isPart(TDF_Label aLabel) const {
    return mShapeTool->IsReference(aLabel);
}

bool PartDocumentImporter::isAssembly(TDF_Label aLabel) const {
    return mShapeTool->IsAssembly(aLabel);
}

PrototypeLabel PartDocumentImporter::importPrototype(TDF_Label aProtoLabel) {
    PartPrototype proto = mShapeTool->GetShape(aProtoLabel);
    if (proto.IsNull()){
        throw PartDocumentImporterExceptions::CouldNotGetShapeFromLabel(
            "GetShape returns Null shape"
        );
    }
    return mDest.addPrototype(proto);
}

void PartDocumentImporter::importPart(
    TDF_Label aPartLabel,
    std::optional<PartLabel> aDestParentLabel
) {
    auto partProtoLabel = importPartPrototype(aPartLabel);
    PartLabel destPartLabel;
    auto loc = mShapeTool->GetLocation(aPartLabel);
    if (aDestParentLabel){
        auto parent = Part(*aDestParentLabel);
        destPartLabel = parent.addComponent(partProtoLabel, loc);
    } else {
        destPartLabel = mDest.addPart(partProtoLabel, loc);
    }
    if (isAssembly(aPartLabel)){
        importPartComponents(aPartLabel, destPartLabel);
    }
}

PrototypeLabel PartDocumentImporter::importPartPrototype(TDF_Label aPartLabel){
    PrototypeLabel partProtoLabel; 
    if (isPrototype(aPartLabel)){
        return importPrototype(aPartLabel);
    } 
    TDF_Label referredLabel;
    mShapeTool->GetReferredShape(aPartLabel, referredLabel);
    if (referredLabel.IsNull()){
        PartPrototype proto = mShapeTool->GetShape(aPartLabel);
        partProtoLabel = importPrototype(aPartLabel);
    } else {
        partProtoLabel = importPrototype(referredLabel);
    }
    return partProtoLabel;
}


void PartDocumentImporter::importPartComponents(
    TDF_Label aSrcCompLabel,
    PartLabel aDestParentLabel
) {
    TDF_LabelSequence srcCompChildrenLabels;
    mShapeTool->GetComponents(aSrcCompLabel, srcCompChildrenLabels);
    for (auto srcCompChildLabel : srcCompChildrenLabels){
        importPart(srcCompChildLabel, aDestParentLabel);
    }
}