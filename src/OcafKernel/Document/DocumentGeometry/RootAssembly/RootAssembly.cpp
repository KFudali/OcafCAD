#include "RootAssembly.hpp"
#include <TopoDS_Compound.hxx>

#include "DocLabelUtils.hpp"
#include "RootAssemblyMarkerAttribute.hpp"

RootAssembly::RootAssembly(Handle(TDocStd_Document) aDoc)
 :  mDoc(aDoc),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aDoc->Main()))
{
    TDF_Label label = mShapeTool->NewShape();
    mLabel = DocLabel(label);
    mLabel.label().AddAttribute(new RootAssemblyMarkerAttribute());
}

bool RootAssembly::isRootAssembly(TDF_Label aLabel) {
    return DocLabelUtils::isRootAssemblyLabel(aLabel);
}

void RootAssembly::clear(){}; 

std::vector<PartLabel> RootAssembly::freeParts() const {
    std::vector<PartLabel> parts;
    TDF_LabelSequence labels;
    mShapeTool->GetComponents(mLabel.label(), labels);
    for (auto label : labels) {
        auto docLabel = DocLabel(label);
        auto address = docLabel.toString();
        auto topLevel = mShapeTool->IsTopLevel(label);
        auto free = mShapeTool->IsFree(label);
        if (PartLabel::isPartLabel(label) && mShapeTool->IsFree(label)){
            parts.push_back(PartLabel(label));
        }
    }
    return parts;
}

std::vector<PartLabel> RootAssembly::topLevelParts() const {
    std::vector<PartLabel> parts;
    TDF_LabelSequence labels;
    mShapeTool->GetComponents(mLabel.label(), labels);
    for (auto label : labels) {
        if (PartLabel::isPartLabel(label)){
            parts.push_back(PartLabel(label));
        }
    }
    return parts;
}
PartLabel RootAssembly::addPart(
    PrototypeLabel aPrototypeLabel, 
    Location aLocation
){
    TDF_Label label = mShapeTool->AddComponent(
        mLabel.label(),
        aPrototypeLabel.label(),
        aLocation
    );
    return PartLabel(label);
};

PartLabel RootAssembly::addEmptyPart(){
    auto shape = mShapeTool->NewShape();
    auto label = mShapeTool->AddComponent(mLabel.label(), shape, Location());
    return PartLabel(label);
}

PartLabel RootAssembly::addEmptyAssembly(){
    auto shape = mShapeTool->NewShape();
    auto label = mShapeTool->AddComponent(mLabel.label(), shape, Location());
    mShapeTool->Expand(label);
    bool ass = mShapeTool->IsAssembly(label);
    return PartLabel(label);
}


void RootAssembly::removePart(PartLabel aPartLabel){}