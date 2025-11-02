#include "NamedSelectionLabel.hpp"
#include "NamedSelectionAttribute.hpp"


#include <TDF_Label.hxx>
#include <TDF_Attribute.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Reference.hxx>

NamedSelectionLabel::NamedSelectionLabel(
    TDF_Label aParentLabel,
    TDF_Label aSubShapeLabel,
    const std::string& aName
){
    auto namingLabel = findExistingNamedSelection(aParentLabel, aSubShapeLabel);
    if (!namingLabel.IsNull()){
        Handle(NamedSelectionAttribute) attr;
        if (!namingLabel.FindAttribute(NamedSelectionAttribute::GetID(), attr)) {
            throw std::runtime_error("Naming label should have selection attr.");
        }
        attr->SetName(aName.c_str());
        mLabel = namingLabel;
        return;
    }

    mLabel =  aParentLabel.NewChild();
    Handle(NamedSelectionAttribute) attr;
    if (!mLabel.FindAttribute(NamedSelectionAttribute::GetID(), attr)) {
        attr = new NamedSelectionAttribute();
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

NamedSelectionLabel::NamedSelectionLabel(TDF_Label aNamingLabel)
{
    if (aNamingLabel.IsNull()) {
        throw std::runtime_error("Named selection label is null");
    }
    Handle(NamedSelectionAttribute) nameAttr;
    if (!aNamingLabel.FindAttribute(NamedSelectionAttribute::GetID(), nameAttr)) {
        throw std::runtime_error("Label does not contain a NamedSelectionAttribute");
    }
    Handle(TDF_Reference) refAttr;
    if (!aNamingLabel.FindAttribute(TDF_Reference::GetID(), refAttr)) {
        throw std::runtime_error("Label does not contain a TDataStd_Reference to a subshape");
    }

    mLabel = aNamingLabel;
}

TDF_Label NamedSelectionLabel::findExistingNamedSelection(
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

std::string NamedSelectionLabel::name() const {
    if (mLabel.IsNull()) {
        return "";
    }
    Handle(NamedSelectionAttribute) attr;
    if (mLabel.FindAttribute(NamedSelectionAttribute::GetID(), attr)) {
        auto occName = attr->GetName();
        Standard_Integer utf8Len = occName.LengthOfCString();
        Standard_PCharacter utf8CString = new char[utf8Len];
        occName.ToUTF8CString(utf8CString);
        return std::string(utf8CString);
    }
    return "";
}

bool NamedSelectionLabel::rename(const std::string& aNewName) {
    if (mLabel.IsNull()) {
        return false;
    }
    Handle(NamedSelectionAttribute) attr;
    if (!mLabel.FindAttribute(NamedSelectionAttribute::GetID(), attr)) {
        return false;
    }

    attr->Set(TCollection_ExtendedString(aNewName.c_str()));
    return true;
}

TDF_Label NamedSelectionLabel::referredLabel() const {
    Handle(TDF_Reference) refAttr;
    mLabel.FindAttribute(TDF_Reference::GetID(), refAttr);
    return refAttr->Get();
}