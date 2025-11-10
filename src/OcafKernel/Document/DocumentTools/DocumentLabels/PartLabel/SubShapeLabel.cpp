#include "SubShapeLabel.hpp"
#include "DocLabelUtils.hpp"
#include "SubShapeMarkerAttribute.hpp"

SubShapeLabel::SubShapeLabel(TDF_Label aLabel) : DocLabel(aLabel){
    if (aLabel.IsAttribute(SubShapeMarkerAttribute::GetID())){
        return;
    }
    if (DocLabelUtils::canBeSubShapeLabel(aLabel)){
        aLabel.AddAttribute(new SubShapeMarkerAttribute());
        return;
    }
    throw LabelIsNotASubShapeLabel("Cannot attach SubShapeMarkerAttribute.");
}

bool SubShapeLabel::isSubShapeLabel(TDF_Label aLabel){
    return aLabel.IsAttribute(SubShapeMarkerAttribute::GetID());
}