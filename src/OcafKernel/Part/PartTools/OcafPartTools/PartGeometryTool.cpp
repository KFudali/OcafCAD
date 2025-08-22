#include "PartGeometryTool.hpp"

PartGeometryTool::PartGeometryTool(PartLabel aPartLabel)
:   mLabel(aPartLabel),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label())) {}

PartPrototype PartGeometryTool::prototype() const {
    return mShapeTool->GetShape(mLabel.label());
}

Location PartGeometryTool::location() const {
    return mShapeTool->GetLocation(mLabel.label());
}

bool PartGeometryTool::setPrototype(PartPrototype aPrototype) {
    return false;
}

bool PartGeometryTool::setLocation(Location aLocation) {
   return false; 
};