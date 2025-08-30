#include "PartGeometryTool.hpp"

PartGeometryTool::PartGeometryTool(PartLabel aPartLabel)
:   mLabel(aPartLabel),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label())) {}

PartPrototype PartGeometryTool::prototype() const {
    TDF_Label prototypeLabel;
    mShapeTool->GetReferredShape(mLabel.label(), prototypeLabel);
    return mShapeTool->GetShape(prototypeLabel);
}

Location PartGeometryTool::location() const {
    return mShapeTool->GetLocation(mLabel.label());
}

bool PartGeometryTool::setPrototype(PartPrototype aPrototype) {
    mShapeTool->SetShape(mLabel.label(), aPrototype);
    return true;
}

bool PartGeometryTool::setLocation(Location aLocation) {
    TDF_Label refLabel;
    mShapeTool->SetLocation(mLabel.label(), aLocation, refLabel);
    return false; 
};