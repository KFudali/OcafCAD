#include "PrototypeLabel.hpp"
#include "DocLabelUtils.hpp"
#include "PrototypeMarkerAttribute.hpp"

PrototypeLabel::PrototypeLabel(TDF_Label aLabel) : DocLabel(aLabel){
    if (aLabel.IsAttribute(PrototypeMarkerAttribute::GetID())){
        return;
    }
    if (DocLabelUtils::isPrototypeLabel(aLabel)){
        aLabel.AddAttribute(new PrototypeMarkerAttribute());
        return;
    }
    throw LabelIsNotAPrototypeLabel("Label is not a Prototype label.");
}