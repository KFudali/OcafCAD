#include "PartSubShapeTool.hpp"

#include <numeric>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS_Shape.hxx>

PartSubShapeTool::PartSubShapeTool(const PartLabel& aPartLabel)
    : mPartLabel(aPartLabel), 
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label()))
{}

TopTools_IndexedMapOfShape PartSubShapeTool::subShapeMap(
    const ShapeType& aShapeType
) const {
    TopoDS_Shape rootShape = mShapeTool->GetShape(mPartLabel.label());
    TopTools_IndexedMapOfShape map;
    if (rootShape.IsNull()) {
        return map;
    }
    TopExp::MapShapes(rootShape, aShapeType, map);
    return map;
}

bool PartSubShapeTool::subShapeIdValid(const SubShapeId& aSubShapeId) const
{
    if (aSubShapeId.root() != mPartLabel) {
        return false;
    }
    auto map = subShapeMap(aSubShapeId.shapeType());
    const int id = aSubShapeId.subId();
    return id > 0 && id <= map.Extent();
}

SubShapeId PartSubShapeTool::subShapeId(const Shape& aPartShape) const
{
    TopoDS_Shape rootShape = mShapeTool->GetShape(mPartLabel.label());
    if (rootShape.IsNull()) {
        return SubShapeId();
    }
    if (aPartShape.IsNull()) {
        return SubShapeId();
    }
    auto map = subShapeMap(aPartShape.ShapeType());
    int id = map.FindIndex(aPartShape);
    if (id == 0) {
        return SubShapeId();
    }
    return SubShapeId(mPartLabel.label(), aPartShape.ShapeType(), id);
}

SubShapeId PartSubShapeTool::subShapeId(const SubShapeLabel& aSubShapeLabel) const
{
    TopoDS_Shape subShape = mShapeTool->GetShape(aSubShapeLabel.label());
    return subShapeId(subShape);
}

Shape PartSubShapeTool::subShape(const SubShapeId& aSubShapeId) const
{
    if (!subShapeIdValid(aSubShapeId)) {
        return Shape();
    }
    auto map = subShapeMap(aSubShapeId.shapeType()); 
    const int idx = aSubShapeId.subId();
    TopoDS_Shape sub = map.FindKey(idx);
    return sub;
}

SubShapeLabel PartSubShapeTool::subShapeLabel(const SubShapeId& aSubShapeId) const
{
    if (!subShapeIdValid(aSubShapeId)) {
        return SubShapeLabel();
    }
    auto map = subShapeMap(aSubShapeId.shapeType()); 
    
    const int idx = aSubShapeId.subId();
    TopoDS_Shape subShape = map.FindKey(idx);
    return subShapeLabel(subShape);
}

SubShapeLabel PartSubShapeTool::subShapeLabel(const Shape& aSubShape) const
{
    TDF_Label mainShapeLabel;
    TDF_Label subShapeLabel;
    mShapeTool->GetReferredShape(mPartLabel.label(), mainShapeLabel);
    mShapeTool->AddSubShape(mainShapeLabel, aSubShape, subShapeLabel);
    if(mainShapeLabel.IsNull() || subShapeLabel.IsNull()){
        return SubShapeLabel();
    } else {
        return SubShapeLabel(subShapeLabel);
    }
}

TDF_LabelSequence PartSubShapeTool::subShapeLabels(
    const SubShapeIdList& aSubShapeList
) const {
    TDF_LabelSequence seq;
    auto map = subShapeMap(aSubShapeList.shapeType());
    for(auto id : aSubShapeList.subIdVec()){
        auto subLabel = subShapeLabel(map.FindKey(id));
        seq.Append(subLabel.label());
    }
    return seq;
}

SubShapeIdList PartSubShapeTool::subShapeIds(
    const TDF_LabelSequence& aSubShapeLabels
) const {
    std::vector<int> ids;
    ids.reserve(aSubShapeLabels.Size());
    auto shape = mShapeTool->GetShape(aSubShapeLabels.First());
    auto shapeType = shape.ShapeType();
    auto map = subShapeMap(shapeType);
    for(auto subLabel : aSubShapeLabels){
        shape = mShapeTool->GetShape(subLabel);
        if(shape.IsNull()){ continue;}
        if(shape.ShapeType() != shapeType){continue;}
        auto id = map.FindIndex(shape);
        ids.push_back(id);
    }
    return SubShapeIdList(mPartLabel, shapeType, ids);
}


SubShapeIdList PartSubShapeTool::subShapesOfType(const ShapeType& aShapeType) const
{
    TopoDS_Shape rootShape = mShapeTool->GetShape(mPartLabel.label());
    if (rootShape.IsNull()) {
        return SubShapeIdList();
    }

    TopTools_IndexedMapOfShape map;
    TopExp::MapShapes(rootShape, aShapeType, map);
    std::vector<int> subIds(map.Extent());
    std::iota(subIds.begin(), subIds.end(), 1); 

    return SubShapeIdList(mPartLabel, aShapeType, subIds);
}