#include "PrototypeLabel.hpp"
#include "DocLabelUtils.hpp"

PrototypeLabel::PrototypeLabel(TDF_Label aLabel) : DocLabel(aLabel){
    bool isPrototypeLabel = DocLabelUtils::isPrototypeLabel(aLabel);
    if (!isPrototypeLabel) {
        throw LabelIsNotAPrototypeLabel("Label is not a Prototype label.");
    }
}