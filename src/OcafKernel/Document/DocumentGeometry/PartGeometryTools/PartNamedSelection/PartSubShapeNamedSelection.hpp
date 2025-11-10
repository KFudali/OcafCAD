#ifndef PartSubShapeNamedSelection_hpp
#define PartSubShapeNamedSelection_hpp

#include "PartSubShapeSelectionBase.hpp"
#include "NamedRefTreeLabel.hpp"

class PartSubShapeNamedSelection : public PartSubShapeSelectionBase {
public:
    PartSubShapeNamedSelection(
        const PartLabel& aPartLabel,
        const TDF_Label& aParentLabel,
        const TDF_LabelSequence& aSubShapeLabels,
        const std::string& aName
    );
    PartSubShapeNamedSelection(
        const PartLabel& aPartLabel,
        const NamedRefTreeLabel& namedSelectionLabel
    );

    std::string name() const noexcept;
    bool rename(const std::string& newName);

private:
    NamedRefTreeLabel mNamedRefTreeLabel;
};

#endif
