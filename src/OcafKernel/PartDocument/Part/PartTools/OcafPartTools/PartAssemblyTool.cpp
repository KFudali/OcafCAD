#include "PartAssemblyTool.hpp"
#include "DocLabelUtils.hpp"

#include <TDataStd_TreeNode.hxx>
#include <XCAFDoc.hxx>

PartAssemblyTool::PartAssemblyTool(PartLabel aPartLabel) 
  : mPartLabel(aPartLabel),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label())) {}

bool PartAssemblyTool::isAssembly() const {
   return mShapeTool->IsAssembly(mPartLabel.label()); 
};

bool PartAssemblyTool::isComponent() const {
    auto label = mPartLabel.label();
    bool isOcafComponent = mShapeTool->IsComponent(label);
    if (!isOcafComponent) {
        return false;
    }
    auto parent = parentAssembly();
    return parent.isValid(); 
}
std::vector<PartLabel> PartAssemblyTool::childrenComponents() const {
    TDF_LabelSequence componentLabels;
    mShapeTool->GetComponents(mPartLabel.label(), componentLabels);
    std::vector<PartLabel> components;
    for(auto label : componentLabels) {
        components.push_back(PartLabel(label));
    }
    return components;
};

PartLabel PartAssemblyTool::parentAssembly() const {
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

bool PartAssemblyTool::addComponent(PartLabel aPartLabel) {return false;};
bool PartAssemblyTool::removeComponent(PartLabel aPartLabel) {return false;};
