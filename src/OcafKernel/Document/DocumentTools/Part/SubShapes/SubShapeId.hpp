#ifndef SubShapeId_hpp
#define SubShapeId_hpp

#include "PartLabel.hpp"
#include "ShapeType.hpp"

class SubShapeId
{
public:
    SubShapeId(const PartLabel& aPartLabel, int subId)
        : mSubId(subId), mParentLabel(aPartLabel) {}
    virtual ~SubShapeId() = default;

    SubShapeId() = default;

    inline PartLabel root() const { return mParentLabel; }
    inline int subId() const { return mSubId; }

private:
    int mSubId = -1;
    PartLabel mParentLabel{};
};

class TypedSubShapeId : public SubShapeId {
    public:
    TypedSubShapeId(
        const PartLabel& aPartLabel, 
        const ShapeType& aShapeType, 
        int subId
    ) : SubShapeId(aPartLabel, subId), mShapeType(aShapeType) {}

    TypedSubShapeId(
        const SubShapeId& aSubShapeId,
        const ShapeType& aShapeType
    ) : SubShapeId(aSubShapeId), mShapeType(aShapeType) {};
    
    TypedSubShapeId() = default;

    inline ShapeType shapeType() const {return mShapeType;};

    private:
    ShapeType mShapeType = ShapeType::TopAbs_SOLID;
};


#endif