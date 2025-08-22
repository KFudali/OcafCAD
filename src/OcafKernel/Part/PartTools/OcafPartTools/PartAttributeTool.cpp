#include "PartAttributeTool.hpp"
#include <TDataStd_Name.hxx>
#include <Standard_Handle.hxx>

PartAttributeTool::PartAttributeTool(PartLabel aPartLabel)
:   mPartLabel(aPartLabel),
    mColorTool(XCAFDoc_DocumentTool::ColorTool(aPartLabel.label())),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label())) {}

std::string PartAttributeTool::name() const {
    Handle(TDataStd_Name) nameAttr;
    if (mPartLabel.label().FindAttribute(TDataStd_Name::GetID(), nameAttr)) {
        TCollection_ExtendedString occName = nameAttr->Get();
        Standard_Integer utf8Len = occName.LengthOfCString();
        Standard_PCharacter utf8CString = new char[utf8Len];
        occName.ToUTF8CString(utf8CString);
        return std::string(utf8CString);
    }
    throw PartDoesNotHaveAttribute("Part does not have a name attribute");
}

ColorRGBA PartAttributeTool::color() const {
    if (mColorTool->IsSet(mPartLabel.label(), XCAFDoc_ColorGen)) {
        Quantity_Color qcolor;
        mColorTool->GetColor(mPartLabel.label(), XCAFDoc_ColorGen, qcolor);
        return ColorRGBA(qcolor.Red(), qcolor.Green(), qcolor.Blue(), 1.0);
    }
    throw PartDoesNotHaveAttribute("Part does not have a color attribute");
}

bool PartAttributeTool::setName(const std::string& aName) {
    try {
        TDataStd_Name::Set(mPartLabel.label(), aName.c_str());
        return true;
    } catch (...) {
        return false;
    }
}

bool PartAttributeTool::setColor(const ColorRGBA& aColor) {
    try {
        Quantity_Color color(
            aColor.GetRGB().Red(), 
            aColor.GetRGB().Green(), 
            aColor.GetRGB().Blue(), 
            Quantity_TOC_RGB
        );
        mColorTool->SetColor(mPartLabel.label(), color, XCAFDoc_ColorGen);
        return true;
    } catch (...) {
        return false;
    }
}

bool PartAttributeTool::hasName() const {
    Handle(TDataStd_Name) nameAttr;
    return mPartLabel.label().FindAttribute(TDataStd_Name::GetID(), nameAttr);
}
bool PartAttributeTool::hasColor() const {
    return mColorTool->IsSet(mPartLabel.label(), XCAFDoc_ColorGen);
}