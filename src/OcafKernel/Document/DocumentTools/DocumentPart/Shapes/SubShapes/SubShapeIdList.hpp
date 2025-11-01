#ifndef SubShapeIdList_hpp
#define SubShapeIdList_hpp

#include "PartLabel.hpp"
#include "ShapeType.hpp"
#include <vector>

class SubShapeIdList
{
public:

    SubShapeIdList(const PartLabel& aPartLabel, const std::vector<int>& subIds)
        : mSubIds(subIds), mParentLabel(aPartLabel) {}

    SubShapeIdList(const PartLabel& aPartLabel)
        : mParentLabel(aPartLabel) {}

    SubShapeIdList() = default;
    virtual ~SubShapeIdList() = default;

    inline PartLabel root() const { return mParentLabel; }
    inline std::vector<int> subIds() const { return mSubIds; }

private:
    std::vector<int> mSubIds{};
    PartLabel mParentLabel{};
};

class TypedSubShapeIdList : public SubShapeIdList {
    public:
    TypedSubShapeIdList(
        const PartLabel& aPartLabel,
        const ShapeType& aShapeType,
        const std::vector<int>& subIds
    ) : SubShapeIdList(aPartLabel, subIds), mShapeType(aShapeType){}

    TypedSubShapeIdList(
        const PartLabel& aPartLabel,
        const ShapeType& aShapeType
    ) : SubShapeIdList(aPartLabel), mShapeType(aShapeType) {}

    TypedSubShapeIdList() = default;
    private:
    ShapeType mShapeType = ShapeType::TopAbs_SOLID;
};

#endif