#include "NamedSelection.hpp"

#include <XCAFDoc_ShapeTool.hxx>

#include "PartSubShapeTool.hpp"
#include "PartShapeTool.hpp"

NamedSelection::NamedSelection(
    const NamedSelectionLabel& aNamedSelectionLabel
) : mSelectionLabel(aNamedSelectionLabel){

}

SubShapeId NamedSelection::namedShapeId() const {
    auto parentPartLabel = mSelectionLabel.label().Father().Father();
    PartSubShapeTool subShapeTool(parentPartLabel);
    PartShapeTool shapeTool(parentPartLabel);
    auto subShape = shapeTool.occShapeTool()->GetShape(
        mSelectionLabel.referredLabel()
    );
    return subShapeTool.subShapeId(subShape);
}