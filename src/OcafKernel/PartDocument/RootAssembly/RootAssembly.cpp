#include "RootAssembly.hpp"
#include "RootAssemblyAttribute.hpp"
#include "DocLabelUtils.hpp"

RootAssembly::RootAssembly(Handle(TDocStd_Document) aDoc)
 :  mDoc(aDoc),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aDoc->Main()))
{
    TDF_Label label = mShapeTool->NewShape();
    mLabel = DocLabel(label);
    mLabel.label().AddAttribute(new RootAssemblyAttribute());
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
        parts.push_back(PartLabel(label));
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

void RootAssembly::removePart(PartLabel aPartLabel){}