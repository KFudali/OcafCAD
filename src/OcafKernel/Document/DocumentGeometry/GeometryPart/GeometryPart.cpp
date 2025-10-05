#include "GeometryPart.hpp"

GeometryPart::GeometryPart(const PartLabel& aPartLabel)
  : Part(aPartLabel){}

bool GeometryPart::setPrototype(const PartPrototype& aPrototype) {
    mShapeTool->SetShape(mPartLabel.label(), aPrototype);
    return true;
}

bool GeometryPart::setLocation(const Location& aLocation) {
    TDF_Label refLabel;
    mShapeTool->SetLocation(mPartLabel.label(), aLocation, refLabel);
    return false; 
};

PartLabel GeometryPart::addEmptyComponent(){
    auto newEmpty = mShapeTool->NewShape();
    auto label = mShapeTool->AddComponent(
        mPartLabel.label(), 
        newEmpty,
        Location()
    );
    return PartLabel(label);
}

bool GeometryPart::expandToAssembly() {
    bool expanded = mShapeTool->Expand(mPartLabel.label());
    if (expanded){
        return true;
    }
    return isAssembly();
}

PartLabel GeometryPart::addComponent(
    PrototypeLabel aProtoLabel, 
    Location aLocation
) {
    auto proto = mShapeTool->GetShape(aProtoLabel.label());
    auto label = mShapeTool->AddComponent(
        mPartLabel.label(), proto
    );
    TDF_Label ref;
    mShapeTool->SetLocation(label, aLocation, ref);
    return PartLabel(label);
};

PartLabel GeometryPart::addComponent(
    PartLabel aPartLabel,
    Location aLocation
) {
    TDF_Label protoLabel;
    mShapeTool->GetReferredShape(aPartLabel.label(), protoLabel);
    if (protoLabel.IsNull()) {
        return PartLabel();
    }
    return addComponent(PrototypeLabel(protoLabel), aLocation);
}

bool GeometryPart::removeComponent(PartLabel aPartLabel) {
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