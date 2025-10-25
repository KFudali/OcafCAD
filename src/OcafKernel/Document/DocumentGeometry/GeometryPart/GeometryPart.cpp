#include "GeometryPart.hpp"
#include "NamedSelectionTreeMarkerAttribute.hpp"
#include "GeometryNamedSelectionAttribute.hpp"
#include <TDF_ChildIterator.hxx>

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

GeometryNamedSelection GeometryPart::addNamedSelection(
    const SubShapeId& aSubShapeId, 
    const std::string& aName
) {
    auto subShape = mSubShapes.subShape(aSubShapeId);
    TDF_Label protoLabel;
    auto prototype = mShapeTool->GetReferredShape(mPartLabel.label(), protoLabel);

    TDF_Label subShapeLabel;
    mShapeTool->FindSubShape(protoLabel, subShape, subShapeLabel);
    if(subShapeLabel.IsNull()){
        subShapeLabel = mShapeTool->AddSubShape(protoLabel, subShape);
    }
    TDF_Label namedSelectionTree = namedSelectionTreeLabel();
    GeometryNamedSelection selection(namedSelectionTree, subShapeLabel, aName);
    return selection;
}

TDF_Label GeometryPart::namedSelectionTreeLabel() const
{
    TDF_Label rootLabel = mPartLabel.label();
    TDF_Label foundLabel;

    for (TDF_ChildIterator it(rootLabel); it.More(); it.Next()) {
        TDF_Label child = it.Value();
        Handle(TDF_Attribute) attr;
        if (child.FindAttribute(NamedSelectionTreeMarkerAttribute::GetID(), attr)) {
            foundLabel = child;
            break;
        }
    }

    if (foundLabel.IsNull()) {
        foundLabel = rootLabel.NewChild();
        Handle(NamedSelectionTreeMarkerAttribute) marker = 
            new NamedSelectionTreeMarkerAttribute();
        foundLabel.AddAttribute(marker);
    }

    return foundLabel;
}

std::vector<GeometryNamedSelection> GeometryPart::namedSelections() const
{
    std::vector<GeometryNamedSelection> result;
    TDF_Label treeLabel = namedSelectionTreeLabel();
    for (TDF_ChildIterator it(treeLabel); it.More(); it.Next()) {
        TDF_Label child = it.Value();

        Handle(GeometryNamedSelectionAttribute) attr;
        if (child.FindAttribute(GeometryNamedSelectionAttribute::GetID(), attr)) {
            result.emplace_back(child);
        }
    }
    return result;
}


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
    if (!isAssembly()) {
        if(!expandToAssembly()){
            return PartLabel();
        }
    }
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