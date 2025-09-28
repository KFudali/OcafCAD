#ifndef ShapeIds_hpp
#define ShapeIds_hpp

#include "PartLabel.hpp"
#include <TopAbs_ShapeEnum.hxx>
#include <vector>

using ShapeType = TopAbs_ShapeEnum;

struct SubShapeId {
    int idInParent{};

    SubShapeId() = default;
    explicit SubShapeId(int id) : idInParent(id) {}
};

struct TypedSubShapeId : public SubShapeId {
    ShapeType shapeType{};

    TypedSubShapeId() = default;
    TypedSubShapeId(int id, ShapeType type)
        : SubShapeId(id), shapeType(type) {}
};

struct SubShapeIdList {
    PartLabel parentLabel{};
    std::vector<int> idsInParent{};

    SubShapeIdList() = default;
    SubShapeIdList(PartLabel parent, std::vector<int> ids)
        : parentLabel(std::move(parent)), idsInParent(std::move(ids)) {}
};

struct TypedSubShapeIdList : public SubShapeIdList {
    ShapeType shapeType{};

    TypedSubShapeIdList() = default;
    TypedSubShapeIdList(PartLabel parent, std::vector<int> ids, ShapeType type)
        : SubShapeIdList(std::move(parent), std::move(ids)), shapeType(type) {}
};

#endif
