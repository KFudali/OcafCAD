#include "PartLabel.hpp"
#include "DocLabelUtils.hpp"
#include "PartMarkerAttribute.hpp"

PartLabel::PartLabel(TDF_Label aLabel) : DocLabel(aLabel){
    if (aLabel.IsAttribute(PartMarkerAttribute::GetID())){
        return;
    }
    if (DocLabelUtils::isPartLabel(aLabel)){
        aLabel.AddAttribute(new PartMarkerAttribute());
        return;
    }
    throw LabelIsNotAPartLabel("Label is not a Part label.");
}
