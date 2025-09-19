#include "PartDocumentImporter.hpp"

#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <TDF_LabelSequence.hxx>
#include "DocLabel.hpp"

void PartDocumentImporter::import(
    Handle(TDocStd_Document) aSrc, 
    PartDocument& aDest,
    AbstractProgressScope& aProgressScope
){
    PartDocumentImporter importer(aSrc, aDest, aProgressScope);
    importer.import();
}

PartDocumentImporter::PartDocumentImporter(
    Handle(TDocStd_Document) aSource,
    PartDocument& aDest,
    AbstractProgressScope& aProgressScope
) : mSrc(aSource), 
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aSource->Main())),
    mColorTool(XCAFDoc_DocumentTool::ColorTool(aSource->Main())),
    mDest(aDest), 
    mProgressScope(aProgressScope) {}

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
    }
    if (isAssembly(aLabel)){
        importAssembly(aLabel);
        return;
    }
    if (isPart(aLabel)) {
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

PartLabel PartDocumentImporter::importPart(TDF_Label aPartLabel) {
    TDF_Label referredLabel;
    mShapeTool->GetReferredShape(aPartLabel, referredLabel);
    if (referredLabel.IsNull()){
        return PartLabel();
    }
    auto loc = mShapeTool->GetLocation(aPartLabel);
    if (isPrototype(referredLabel)){
        auto prototypeLabel = importPrototype(referredLabel);
        return mDest.addPart(prototypeLabel, loc);
    }
    return PartLabel();
}

void PartDocumentImporter::importComponent(
    TDF_Label aSrcCompLabel,
    PartLabel aDestParentLabel
) {
    auto destParent = Part(aDestParentLabel); 

    auto loc = mShapeTool->GetLocation(aSrcCompLabel);
    auto destCompLabel = PartLabel();
    if (isPrototype(aSrcCompLabel)){
        auto proto = importPrototype(aSrcCompLabel);
        destCompLabel = destParent.addComponent(proto, loc);
    }
    if (isPart(aSrcCompLabel)){
        TDF_Label referredLabel;
        mShapeTool->GetReferredShape(aSrcCompLabel, referredLabel);
        if (isPrototype(referredLabel)){
            auto prototypeLabel = importPrototype(referredLabel);
            destParent.addComponent(prototypeLabel, loc);
        }
    }
    if (isAssembly(aSrcCompLabel)){
        auto destComp = Part(destCompLabel);
        TDF_LabelSequence srcCompChildrenLabels;
        mShapeTool->GetComponents(aSrcCompLabel, srcCompChildrenLabels);
        for (auto srcCompChildLabel : srcCompChildrenLabels){
            importComponent(srcCompChildLabel, destCompLabel);
        }
    } 
}

PartLabel PartDocumentImporter::importAssembly(TDF_Label aAssemblyLabel) {
    auto assemblyLabel = mDest.addEmptyAssembly();
    auto assembly = Part(assemblyLabel);
    TDF_LabelSequence srcComponentLabels;
    mShapeTool->GetComponents(aAssemblyLabel, srcComponentLabels);
    for(auto srcCompLabel : srcComponentLabels){
        importComponent(srcCompLabel, assemblyLabel);
    }
    return PartLabel(assemblyLabel);
}