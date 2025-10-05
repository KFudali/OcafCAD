#include "Part.hpp"
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <TDF_LabelSequence.hxx>
#include <TDataStd_Name.hxx>
#include "DocLabelUtils.hpp"


Part::Part(const PartLabel& aPartLabel)
  : mPartLabel(aPartLabel),
    mAttributes(PartAttributeTool(aPartLabel)),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label()))
{
    if (mAttributes.hasColor()) {
        mAttributes.setColor(Part::defaultPartColor);
    }
    if (mAttributes.hasName()) {
        mAttributes.setName(Part::defaultPartName);
    }
}

PartPrototype Part::prototype() const {    
    TDF_Label prototypeLabel;
    mShapeTool->GetReferredShape(mPartLabel.label(), prototypeLabel);
    return mShapeTool->GetShape(prototypeLabel);
}

Location Part::location() const {
    return mShapeTool->GetLocation(mPartLabel.label());
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
    return !DocLabelUtils::isRootAssemblyLabel(parent.label());
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