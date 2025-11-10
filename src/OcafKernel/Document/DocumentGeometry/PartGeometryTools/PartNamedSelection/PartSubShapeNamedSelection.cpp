#include "PartSubShapeNamedSelection.hpp"

PartSubShapeNamedSelection::PartSubShapeNamedSelection(
    const PartLabel& aPartLabel,
    const TDF_Label& aParentLabel,
    const TDF_LabelSequence& aSubShapeLabels,
    const std::string& aName
) : mNamedRefTreeLabel(aParentLabel, aSubShapeLabels, aName),
    PartSubShapeSelectionBase(aPartLabel, &mNamedRefTreeLabel){}

PartSubShapeNamedSelection::PartSubShapeNamedSelection(
    const PartLabel& aPartLabel,
    const NamedRefTreeLabel& namedSelectionLabel
) : mNamedRefTreeLabel(namedSelectionLabel),
    PartSubShapeSelectionBase(aPartLabel, &mNamedRefTreeLabel){}

std::string PartSubShapeNamedSelection::name() const noexcept {
    return mNamedRefTreeLabel.name();
}

bool PartSubShapeNamedSelection::rename(const std::string& newName) {
    return mNamedRefTreeLabel.rename(newName);
}
