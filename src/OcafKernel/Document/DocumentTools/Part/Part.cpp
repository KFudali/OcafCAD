#include "Part.hpp"
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <TDF_LabelSequence.hxx>

bool hasName() const {
    Handle(TDataStd_Name) nameAttr;
    return mPartLabel.label().FindAttribute(TDataStd_Name::GetID(), nameAttr);
}
bool hasColor() const {
    return mColorTool->IsSet(mPartLabel.label(), XCAFDoc_ColorGen);
}

Part::Part(const PartLabel& aPartLabel)
  : mPartLabel(aPartLabel),
    mAttributes(PartAttributeTool(aPartLabel)),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label()))
{
    if (hasColor()) {
        setColor(Part::defaultPartColor);
    }
    if (hasName()) {
        setName(Part::defaultPartName);
    }
}

PartPrototype Part::prototype() const {    
    TDF_Label prototypeLabel;
    mShapeTool->GetReferredShape(mLabel.label(), prototypeLabel);
    return mShapeTool->GetShape(prototypeLabel);
}

Location PartGeometryTool::location() const {
    return mShapeTool->GetLocation(mLabel.label());
}

bool Part::isAssembly() const {
   return mShapeTool->IsAssembly(mPartLabel.label()); 
};

bool Part::isComponent() const {
    auto label = mPartLabel.label();
    bool isOcafComponent = mShapeTool->IsComponent(label);
    if (!isOcafComponent) {
        return false;
    }
    auto parent = parentAssembly();
    return !DocLabelUtils::isRootAssemblyLabel(parent);
}

std::vector<PartLabel> Part::childrenComponents() const {
    TDF_LabelSequence componentLabels;
    mShapeTool->GetComponents(mPartLabel.label(), componentLabels);
    std::vector<PartLabel> components;
    for(auto label : componentLabels) {
        components.push_back(PartLabel(label));
    }
    return components;
};

PartLabel Part::parentAssembly() const {
    TDF_Label parent = mPartLabel.label().Father();
    if (parent.IsNull()){
        return PartLabel();
    }
    if (DocLabelUtils::isRootAssemblyLabel(parent)) {
        return PartLabel();
    } else {
        return PartLabel(parent);
    }
};