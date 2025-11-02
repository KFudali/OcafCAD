#ifndef SubShapeIdList_hpp
#define SubShapeIdList_hpp

#include "PartLabel.hpp"
#include "ShapeType.hpp"
#include <vector>

class SubShapeIdList
{
public:

    SubShapeIdList(
        const PartLabel& aPartLabel, 
        const ShapeType& aShapeType,
        const std::vector<int>& subIds)
        : mSubIds(subIds), mShapeType(aShapeType), mParentLabel(aPartLabel) {}

    SubShapeIdList(const PartLabel& aPartLabel)
        : mParentLabel(aPartLabel) {}

    SubShapeIdList() = default;
    virtual ~SubShapeIdList() = default;

    inline PartLabel root() const { return mParentLabel; }
    inline ShapeType shapeType() const { return mShapeType; }
    inline std::vector<int> subIds() const { return mSubIds; }

private:
    std::vector<int> mSubIds{};
    PartLabel mParentLabel{};
    ShapeType mShapeType = ShapeType::TopAbs_SOLID;
};
#endif