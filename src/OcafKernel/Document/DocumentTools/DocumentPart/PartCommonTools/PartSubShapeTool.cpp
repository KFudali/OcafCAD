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

bool PartSubShapeTool::subShapeIdValid(const SubShapeId& aSubShapeId) const
{
    if (aSubShapeId.root() != mPartLabel) {
        return false;
    }

    TopoDS_Shape shape = mShapeTool->GetShape(mPartLabel.label());
    if (shape.IsNull()) {
        return false;
    }

    TopTools_IndexedMapOfShape map;
    TopExp::MapShapes(shape, aSubShapeId.shapeType(), map);

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
    

    TopTools_IndexedMapOfShape map;
    TopExp::MapShapes(rootShape, aPartShape.ShapeType(), map);
    
    int id = map.FindIndex(aPartShape);
    if (id == 0) {
        return SubShapeId();
    }
    return SubShapeId(mPartLabel.label(), aPartShape.ShapeType(), id);
}

Shape PartSubShapeTool::subShape(const SubShapeId& aSubShapeId) const
{
    if (!subShapeIdValid(aSubShapeId)) {
        return Shape();
    }

    TopoDS_Shape rootShape = mShapeTool->GetShape(mPartLabel.label());
    TopTools_IndexedMapOfShape map;
    TopExp::MapShapes(rootShape, aSubShapeId.shapeType(), map);
    
    const int idx = aSubShapeId.subId();
    TopoDS_Shape sub = map.FindKey(idx);
    return sub;
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