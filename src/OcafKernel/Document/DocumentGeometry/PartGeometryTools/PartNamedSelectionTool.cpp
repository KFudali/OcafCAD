
#include "PartNamedSelectionTool.hpp"

#include "GeometryNamedSelectionAttribute.hpp"
#include "NamedSelectionTreeMarkerAttribute.hpp"
#include "PartSubShapeTool.hpp"

#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Attribute.hxx>

PartNamedSelectionTool::PartNamedSelectionTool(const PartLabel& aPartLabel) :
    mPartLabel(aPartLabel),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label())){}

GeometryNamedSelection PartNamedSelectionTool::addNamedSelection(
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
    GeometryNamedSelection selection(namedSelectionTree, subShapeLabel, aName);
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

std::vector<GeometryNamedSelection> PartNamedSelectionTool::namedSelections() const
{
    std::vector<GeometryNamedSelection> result;
    TDF_Label treeLabel = namedSelectionTreeLabel();
    for (TDF_ChildIterator it(treeLabel); it.More(); it.Next()) {
        TDF_Label child = it.Value();

        Handle(GeometryNamedSelectionAttribute) attr;
        if (child.FindAttribute(GeometryNamedSelectionAttribute::GetID(), attr)) {
            result.emplace_back(child);
        }
    }
    return result;
}