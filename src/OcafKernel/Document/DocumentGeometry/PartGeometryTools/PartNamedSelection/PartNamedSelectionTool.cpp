
#include "PartNamedSelectionTool.hpp"

#include "NamedRefTreeLabel.hpp"
#include "NamedRefTreeAttribute.hpp"
#include "NamedSelectionTreeMarkerAttribute.hpp"

#include <TDF_ChildIterator.hxx>
#include <algorithm>

PartNamedSelectionTool::PartNamedSelectionTool(const PartLabel& aPartLabel) :
    mPartLabel(aPartLabel), mSubShapeTool(aPartLabel){}

PartSubShapeNamedSelection PartNamedSelectionTool::addSelection(
    const SubShapeIdList& aSubShapeIdList, 
    const std::string& aName
) {
    TDF_Label treeRootLabel = namedSelectionTreeLabel();
    auto labels = mSubShapeTool.subShapeLabels(aSubShapeIdList);
    PartSubShapeNamedSelection selection(mPartLabel, treeRootLabel, labels, aName);
    return selection;
}

TDF_Label PartNamedSelectionTool::namedSelectionTreeLabel() const
{
    TDF_Label rootLabel = mPartLabel.label();
    TDF_Label foundLabel;

    for (TDF_ChildIterator it(rootLabel); it.More(); it.Next()) {
        TDF_Label child = it.Value();
        Handle(TDF_Attribute) attr;
        if (child.FindAttribute(NamedSelectionTreeMarkerAttribute::GetID(), attr)) {
            foundLabel = child;
            break;
        }
    }

    if (foundLabel.IsNull()) {
        foundLabel = rootLabel.NewChild();
        Handle(NamedSelectionTreeMarkerAttribute) marker = 
            new NamedSelectionTreeMarkerAttribute();
        foundLabel.AddAttribute(marker);
    }

    return foundLabel;
}

std::vector<PartSubShapeNamedSelection> PartNamedSelectionTool::selections() const
{
    std::vector<PartSubShapeNamedSelection> result;
    TDF_Label treeLabel = namedSelectionTreeLabel();
    for (TDF_ChildIterator it(treeLabel); it.More(); it.Next()) {
        TDF_Label child = it.Value();
        Handle(NamedRefTreeAttribute) attr;
        if (child.FindAttribute(NamedRefTreeAttribute::GetID(), attr)) {
            NamedRefTreeLabel label(child);
            PartSubShapeNamedSelection selection(mPartLabel, label);
            result.push_back(selection);
        }
    }
    return result;
}

bool PartNamedSelectionTool::removeSelection(
    PartSubShapeNamedSelection& aNamedSelection
) {
    aNamedSelection.clear();
    return true;
}