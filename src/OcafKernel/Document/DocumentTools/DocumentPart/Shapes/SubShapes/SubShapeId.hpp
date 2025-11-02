#ifndef SubShapeId_hpp
#define SubShapeId_hpp

#include "PartLabel.hpp"
#include "ShapeType.hpp"

class SubShapeId
{
public:
    SubShapeId(
        const PartLabel& aPartLabel, 
        const ShapeType& aShapeType, 
        int subId
    ) : mSubId(subId), mParentLabel(aPartLabel), mShapeType(aShapeType) {}
    virtual ~SubShapeId() = default;

    SubShapeId() = default;

    inline PartLabel root() const { return mParentLabel; }
    inline int subId() const { return mSubId; }
    inline ShapeType shapeType() const {return mShapeType;};

    bool operator==(const SubShapeId& other) const
    {
        return mSubId == other.mSubId
            && mShapeType == other.mShapeType
            && mParentLabel == other.mParentLabel;
    }
    bool operator!=(const SubShapeId& other) const
    {
        return !(*this == other);
    }

    private:
    int mSubId = -1;
    PartLabel mParentLabel{};
    ShapeType mShapeType = ShapeType::TopAbs_SOLID;
};

#endif