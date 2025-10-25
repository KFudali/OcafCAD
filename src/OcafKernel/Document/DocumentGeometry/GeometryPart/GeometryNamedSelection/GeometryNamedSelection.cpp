#include "GeometryNamedSelection.hpp"
#include "GeometryNamedSelectionAttribute.hpp"
#include <TDF_Label.hxx>
#include <TDF_Attribute.hxx>

GeometryNamedSelection::GeometryNamedSelection(const std::string& aName, TDF_Label aSubShapeLabel)
  : mLabel(aSubShapeLabel)
{
    if (mLabel.IsNull()) {
        return;
    }

    Handle(GeometryNamedSelectionAttribute) attr;
    if (!mLabel.FindAttribute(GeometryNamedSelectionAttribute::GetID(), attr)) {
        attr = new GeometryNamedSelectionAttribute();
        attr->SetName(TCollection_ExtendedString(aName.c_str()));
        mLabel.AddAttribute(attr);
    }
    else {
        attr->SetName(TCollection_ExtendedString(aName.c_str()));
    }
}

std::string GeometryNamedSelection::name() const {
    if (mLabel.IsNull()) {
        return "";
    }
    Handle(GeometryNamedSelectionAttribute) attr;
    if (mLabel.FindAttribute(GeometryNamedSelectionAttribute::GetID(), attr)) {
        auto occName = attr->GetName();
        Standard_Integer utf8Len = occName.LengthOfCString();
        Standard_PCharacter utf8CString = new char[utf8Len];
        occName.ToUTF8CString(utf8CString);
        return std::string(utf8CString);
    }
    return "";
}

bool GeometryNamedSelection::rename(const std::string& aNewName) {
    if (mLabel.IsNull()) {
        return false;
    }
    Handle(GeometryNamedSelectionAttribute) attr;
    if (!mLabel.FindAttribute(GeometryNamedSelectionAttribute::GetID(), attr)) {
        return false;
    }

    attr->Set(TCollection_ExtendedString(aNewName.c_str()));
    return true;
}
