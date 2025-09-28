#include "GeometryObject.hpp"
#include "TopExp.hxx"
#include <stdexcept>

#include "GeometryObject.hpp"
#include "TopExp.hxx"
#include "TopAbs_ShapeEnum.hxx"
#include "TopTools_IndexedMapOfShape.hxx"
#include <stdexcept>

PartPrototype GeometryObject::getSubShape(const SubShapeId& aShapeId) const {
    TopTools_IndexedMapOfShape subShapes;
    TopExp::MapShapes(mSourcePart.prototype(), subShapes);

    if (aShapeId.idInParent <= 0 || aShapeId.idInParent > subShapes.Extent()) {
        throw std::out_of_range("Invalid SubShapeId index.");
    }

    return subShapes.FindKey(aShapeId.idInParent);
}

PartPrototype GeometryObject::getTypedSubShape(const TypedSubShapeId& aShapeId) const {
    TopTools_IndexedMapOfShape subShapes;
    TopExp::MapShapes(mSourcePart.prototype(), aShapeId.shapeType, subShapes);
    if (aShapeId.idInParent <= 0 || aShapeId.idInParent > subShapes.Extent()) {
        throw std::out_of_range("Invalid SubShapeId index.");
    }
    return subShapes.FindKey(aShapeId.idInParent);
}

SubShapeId GeometryObject::getSubShapeId(const PartPrototype& aPartPrototype) const {
    TopTools_IndexedMapOfShape subShapes;
    TopExp::MapShapes(mSourcePart.prototype(), subShapes);
    int idInParent = subShapes.FindIndex(aPartPrototype);

    if (idInParent == 0) {
        throw std::runtime_error("Shape not found in parent.");
    }

    return SubShapeId{idInParent};
}

static SubShapeIdList collectSubShapes(const Part& sourcePart, const ShapeType& type) {
    TopTools_IndexedMapOfShape subShapes;
    TopExp::MapShapes(sourcePart.prototype(), type, subShapes);

    std::vector<int> ids;
    ids.reserve(subShapes.Extent());
    for (int i = 1; i <= subShapes.Extent(); ++i) {
        ids.push_back(i);
    }

    return SubShapeIdList{sourcePart.partLabel(), std::move(ids)};
}

SubShapeIdList GeometryObject::points() const {
    return collectSubShapes(mSourcePart, TopAbs_VERTEX);
}

SubShapeIdList GeometryObject::edges() const {
    return collectSubShapes(mSourcePart, TopAbs_EDGE);
}

SubShapeIdList GeometryObject::faces() const {
    return collectSubShapes(mSourcePart, TopAbs_FACE);
}

SubShapeIdList GeometryObject::volumes() const {
    return collectSubShapes(mSourcePart, TopAbs_SOLID);
}
