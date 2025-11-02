
#include "PartNamedSelectionTool.hpp"

#include "NamedSelectionLabel.hpp"
#include "NamedSelectionAttribute.hpp"
#include "NamedSelectionTreeMarkerAttribute.hpp"
#include "PartSubShapeTool.hpp"

#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Attribute.hxx>
#include <TDF_Tool.hxx>

PartNamedSelectionTool::PartNamedSelectionTool(const PartLabel& aPartLabel) :
    mPartLabel(aPartLabel),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label())){}

NamedSelection PartNamedSelectionTool::addNamedSelection(
    const SubShapeId& aSubShapeId, 
    const std::string& aName
) {
    auto subShape = PartSubShapeTool(mPartLabel).subShape(aSubShapeId);
    TDF_Label protoLabel;
    auto prototype = mShapeTool->GetReferredShape(mPartLabel.label(), protoLabel);

    TDF_Label subShapeLabel;
    mShapeTool->FindSubShape(protoLabel, subShape, subShapeLabel);
    if(subShapeLabel.IsNull()){
        subShapeLabel = mShapeTool->AddSubShape(protoLabel, subShape);
    }
    TDF_Label namedSelectionTree = namedSelectionTreeLabel();
    NamedSelectionLabel selectionLabel(namedSelectionTree, subShapeLabel, aName);
    return NamedSelection(selectionLabel);
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

std::vector<NamedSelection> PartNamedSelectionTool::namedSelections() const
{
    std::vector<NamedSelection> result;
    TDF_Label treeLabel = namedSelectionTreeLabel();
    for (TDF_ChildIterator it(treeLabel); it.More(); it.Next()) {
        TDF_Label child = it.Value();

        Handle(NamedSelectionAttribute) attr;
        if (child.FindAttribute(NamedSelectionAttribute::GetID(), attr)) {
            NamedSelectionLabel label(child);
            result.emplace_back(label);
        }
    }
    return result;
}

bool PartNamedSelectionTool::removeNamedSelection(
    const NamedSelection& aNamedSelection
) {
    TDF_Label label = aNamedSelection.label().label();
    if (label.IsNull())
        return false;

    TDF_Label root = namedSelectionTreeLabel();
    if (label.Father() != root)
        return false;

    label.ForgetAllAttributes();
    return true;
}