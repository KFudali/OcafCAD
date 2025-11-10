#include "PartSubShapeSelection.hpp"

PartSubShapeSelection::PartSubShapeSelection(
    const PartLabel& aPartLabel,
    const TDF_Label& aParentLabel,
    const TDF_LabelSequence& aSubShapeLabels
) : mRefTreeLabel(aParentLabel, aSubShapeLabels),
    PartSubShapeSelectionBase(aPartLabel, &mRefTreeLabel){}

PartSubShapeSelection::PartSubShapeSelection(
    const PartLabel& aPartLabel,
    const RefTreeLabel& aSelectionLabel
) : mRefTreeLabel(aSelectionLabel),
    PartSubShapeSelectionBase(aPartLabel, &mRefTreeLabel){}