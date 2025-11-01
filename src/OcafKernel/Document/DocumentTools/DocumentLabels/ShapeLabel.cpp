#include "ShapeLabel.hpp"
#include "DocLabelUtils.hpp"
#include "PrototypeMarkerAttribute.hpp"

ShapeLabel::ShapeLabel(TDF_Label aLabel) : DocLabel(aLabel){
    if (aLabel.IsAttribute(PrototypeMarkerAttribute::GetID())){
        return;
    }
    if (DocLabelUtils::canBePrototypeLabel(aLabel)){
        aLabel.AddAttribute(new PrototypeMarkerAttribute());
        return;
    }
    throw LabelIsNotAPrototypeLabel("Label is not a Prototype label.");
}

bool ShapeLabel::isPrototypeLabel(TDF_Label aLabel){
    return aLabel.IsAttribute(PrototypeMarkerAttribute::GetID());
}