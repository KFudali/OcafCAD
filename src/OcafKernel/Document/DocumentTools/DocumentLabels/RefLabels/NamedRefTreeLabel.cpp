#include "NamedRefTreeLabel.hpp"
#include "NamedRefTreeAttribute.hpp"

#include <TDF_Label.hxx>
#include <unordered_set>
#include <stdexcept>

NamedRefTreeLabel::NamedRefTreeLabel(
    const TDF_Label& aParentLabel,
    const TDF_LabelSequence& aShapeLabelsToName,
    const std::string& aName
) : RefTreeLabel(aParentLabel, aShapeLabelsToName) {
    Handle(NamedRefTreeAttribute) attr = new NamedRefTreeAttribute();
    attr->Set(aName.c_str());
    mLabel.AddAttribute(attr);
}

NamedRefTreeLabel::NamedRefTreeLabel(TDF_Label aNamedRefTreeLabel)
    : RefTreeLabel(aNamedRefTreeLabel) {
    Handle(NamedRefTreeAttribute) attr;
    if (!mLabel.FindAttribute(NamedRefTreeAttribute::GetID(), attr)) {
        throw LabelException(
            "Cannot create NamedRefTreeLabel. Label is missing NamedRefTreeAttribute."
        );
    }
}

std::string NamedRefTreeLabel::name() const {
    if (mLabel.IsNull()) {
        return "";
    }
    Handle(NamedRefTreeAttribute) attr;
    if (mLabel.FindAttribute(NamedRefTreeAttribute::GetID(), attr)) {
        auto occName = attr->GetName();
        Standard_Integer utf8Len = occName.LengthOfCString();
        Standard_PCharacter utf8CString = new char[utf8Len];
        occName.ToUTF8CString(utf8CString);
        return std::string(utf8CString);
    }
    return "";
}

bool NamedRefTreeLabel::rename(const std::string& aNewName) {
    if (mLabel.IsNull()) {
        return false;
    }
    Handle(NamedRefTreeAttribute) attr;
    if (!mLabel.FindAttribute(NamedRefTreeAttribute::GetID(), attr)) {
        return false;
    }

    attr->Set(TCollection_ExtendedString(aNewName.c_str()));
    return true;
}