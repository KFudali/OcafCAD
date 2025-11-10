#include "PartSubShapeSelectionBase.hpp"

SubShapeIdList PartSubShapeSelectionBase::ids() const {
    auto refs = mRefTreeLabel->references();
    return mSubShapeTool.subShapeIds(refs);
}

void PartSubShapeSelectionBase::clear() {
    if (mRefTreeLabel) {
        mRefTreeLabel->label().ForgetAllAttributes();
    }
}

bool PartSubShapeSelectionBase::append(const SubShapeId& aSubShapeId) {
    auto shapeLabel = mSubShapeTool.subShapeLabel(aSubShapeId);
    return mRefTreeLabel->appendReference(shapeLabel.label());
}

bool PartSubShapeSelectionBase::remove(const SubShapeId& aSubShapeId) {
    auto shapeLabel = mSubShapeTool.subShapeLabel(aSubShapeId);
    return mRefTreeLabel->removeReference(shapeLabel.label());
}
