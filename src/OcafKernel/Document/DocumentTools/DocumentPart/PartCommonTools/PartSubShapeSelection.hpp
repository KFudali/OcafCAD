#ifndef PartSubShapeSelection_hpp
#define PartSubShapeSelection_hpp

#include "PartSubShapeSelectionBase.hpp"
#include "NamedRefTreeLabel.hpp"

class PartSubShapeSelection : public PartSubShapeSelectionBase {
public:
    PartSubShapeSelection(
        const PartLabel& aPartLabel,
        const TDF_Label& aParentLabel,
        const TDF_LabelSequence& aSubShapeLabels
    );
    PartSubShapeSelection(
        const PartLabel& aPartLabel,
        const RefTreeLabel& aSelectionLabel
    );

private:
    RefTreeLabel mRefTreeLabel;
};

#endif

