#include "PartShapeTool.hpp"

#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <TDF_Label.hxx>

PartShapeTool::PartShapeTool(const PartLabel& aPartLabel)
  : mPartLabel(aPartLabel),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label())){}

Shape PartShapeTool::shape() const {    
    TDF_Label shapeLabel;
    mShapeTool->GetReferredShape(mPartLabel.label(), shapeLabel);
    return mShapeTool->GetShape(shapeLabel);
}

Location PartShapeTool::location() const {
    return mShapeTool->GetLocation(mPartLabel.label());
}