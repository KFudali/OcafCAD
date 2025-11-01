#include "GeometryNamedSelection.hpp"
#include "GeometryNamedSelectionAttribute.hpp"

#include <TDF_Label.hxx>
#include <TDF_Attribute.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Reference.hxx>

GeometryNamedSelection::GeometryNamedSelection(
    TDF_Label aParentLabel,
    TDF_Label aSubShapeLabel,
    const std::string& aName
){
    auto namingLabel = findExistingNamedSelection(aParentLabel, aSubShapeLabel);
    if (!namingLabel.IsNull()){
        Handle(GeometryNamedSelectionAttribute) attr;
        if (!namingLabel.FindAttribute(GeometryNamedSelectionAttribute::GetID(), attr)) {
            throw std::runtime_error("Naming label should have selection attr.");
        }
        attr->SetName(aName.c_str());
        mLabel = namingLabel;
        return;
    }

    mLabel =  aParentLabel.NewChild();
    Handle(GeometryNamedSelectionAttribute) attr;
    if (!mLabel.FindAttribute(GeometryNamedSelectionAttribute::GetID(), attr)) {
        attr = new GeometryNamedSelectionAttribute();
        attr->SetName(TCollection_ExtendedString(aName.c_str()));
        mLabel.AddAttribute(attr);
    }
    else {
        attr->SetName(TCollection_ExtendedString(aName.c_str()));
    }

    Handle(TDF_Reference) refAttr;
    if (!mLabel.FindAttribute(TDF_Reference::GetID(), refAttr)) {
        refAttr = new TDF_Reference();
        refAttr->Set(aSubShapeLabel);
        mLabel.AddAttribute(refAttr);
    } else {
        refAttr->Set(aSubShapeLabel);
    }
}

GeometryNamedSelection::GeometryNamedSelection(TDF_Label aNamingLabel)
{
    if (aNamingLabel.IsNull()) {
        throw std::runtime_error("Named selection label is null");
    }
    Handle(GeometryNamedSelectionAttribute) nameAttr;
    if (!aNamingLabel.FindAttribute(GeometryNamedSelectionAttribute::GetID(), nameAttr)) {
        throw std::runtime_error("Label does not contain a GeometryNamedSelectionAttribute");
    }
    Handle(TDF_Reference) refAttr;
    if (!aNamingLabel.FindAttribute(TDF_Reference::GetID(), refAttr)) {
        throw std::runtime_error("Label does not contain a TDataStd_Reference to a subshape");
    }

    mLabel = aNamingLabel;
}

TDF_Label GeometryNamedSelection::findExistingNamedSelection(
    const TDF_Label& aParentLabel,
    const TDF_Label& aSubShapeLabel
) const{
    for (TDF_ChildIterator it(aParentLabel); it.More(); it.Next()) {
        TDF_Label child = it.Value();
        Handle(TDF_Reference) refAttr;
        if (child.FindAttribute(TDF_Reference::GetID(), refAttr)) {
            if (!refAttr.IsNull() && refAttr->Get() == aSubShapeLabel) {
                return child;
            }
        }
    }
    return TDF_Label();
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
