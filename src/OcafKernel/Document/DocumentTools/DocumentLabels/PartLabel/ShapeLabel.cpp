#include "ShapeLabel.hpp"
#include "DocLabelUtils.hpp"
#include "ShapeMarkerAttribute.hpp"

ShapeLabel::ShapeLabel(TDF_Label aLabel) : DocLabel(aLabel){
    if (aLabel.IsAttribute(ShapeMarkerAttribute::GetID())){
        return;
    }
    if (DocLabelUtils::canBeShapeLabel(aLabel)){
        aLabel.AddAttribute(new ShapeMarkerAttribute());
        return;
    }
    throw LabelIsNotAShapeLabel("Label is not a Prototype label.");
}

bool ShapeLabel::isShapeLabel(TDF_Label aLabel){
    return aLabel.IsAttribute(ShapeMarkerAttribute::GetID());
}