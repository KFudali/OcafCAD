#include "Part.hpp"

#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <TDF_LabelSequence.hxx>
#include <TDataStd_Name.hxx>

#include "DocLabelUtils.hpp"

Part::Part(const PartLabel& aPartLabel)
  : mPartLabel(aPartLabel),
    mAttributes(PartAttributeTool(aPartLabel)),
    mSubShapes(PartSubShapeTool(aPartLabel)),
    mShapes(PartShapeTool(aPartLabel)),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label()))
{
    if (!mAttributes.hasColor()) {
        mAttributes.setColor(Part::defaultPartColor);
    }
    if (!mAttributes.hasName()) {
        mAttributes.setName(Part::defaultPartName);
    }
}

Shape Part::shape() const {
    return mShapes.shape();
}

Location Part::location() const {
    return mShapes.location();
}
