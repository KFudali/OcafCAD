#include "PartLabel.hpp"
#include "DocLabelUtils.hpp"

PartLabel::PartLabel(TDF_Label aLabel) : DocLabel(aLabel){
    bool isPartLabel = DocLabelUtils::isPartLabel(aLabel);
    if (!isPartLabel) {
        throw LabelIsNotAPartLabel("Label is not a Part label.");
    }
}