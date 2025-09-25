#include "PartAssemblyTool.hpp"
#include "DocLabelUtils.hpp"

#include <BRep_Builder.hxx>
#include <TopoDS_Compound.hxx>
#include <TDataStd_TreeNode.hxx>
#include <XCAFDoc.hxx>
#include <ranges>

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

PartLabel PartAssemblyTool::addEmptyComponent(){
    auto newEmpty = mShapeTool->NewShape();
    auto label = mShapeTool->AddComponent(
        mPartLabel.label(), 
        newEmpty,
        Location()
    );
    return PartLabel(label);
}


bool PartAssemblyTool::expandToAssembly() {
    bool expanded = mShapeTool->Expand(mPartLabel.label());
    if (expanded){
        return true;
    }
    return isAssembly();
}

PartLabel PartAssemblyTool::addComponent(
    PrototypeLabel aProtoLabel, 
    Location aLocation
) {
    if (!isAssembly()) {
        expandToAssembly();
    }

    auto proto = mShapeTool->GetShape(aProtoLabel.label());
    auto label = mShapeTool->AddComponent(
        mPartLabel.label(), proto
    );
    TDF_Label ref;
    mShapeTool->SetLocation(label, aLocation, ref);
    return PartLabel(label);
};

PartLabel PartAssemblyTool::addComponent(
    PartLabel aPartLabel,
    Location aLocation
) {
    if (!isAssembly()) {
        if(!expandToAssembly()){
            return PartLabel();
        }
    }
    
    TDF_Label protoLabel;
    mShapeTool->GetReferredShape(aPartLabel.label(), protoLabel);
    if (protoLabel.IsNull()) {
        return PartLabel();
    }
    return addComponent(PrototypeLabel(protoLabel), aLocation);
}

bool PartAssemblyTool::removeComponent(PartLabel aPartLabel) {
    if (!isAssembly()) {
        return false;
    }
    auto components = childrenComponents();
    if (std::ranges::find(components, aPartLabel) != components.end()) {
        mShapeTool->RemoveComponent(aPartLabel.label());
        return true;
    }
    return false;
}