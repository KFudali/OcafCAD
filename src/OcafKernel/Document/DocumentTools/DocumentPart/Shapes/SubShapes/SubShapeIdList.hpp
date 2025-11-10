#ifndef SubShapeIdList_hpp
#define SubShapeIdList_hpp

#include "PartLabel.hpp"
#include "SubShapeId.hpp"
#include "ShapeType.hpp"
#include <vector>
#include <algorithm>
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

    SubShapeIdList(const std::vector<SubShapeId>& aSubIdVec) {
        if (aSubIdVec.size() == 0){ mParentLabel = PartLabel(); } return;
        mParentLabel = aSubIdVec[0].root();
        mShapeType = aSubIdVec[0].shapeType();
        mSubIds.reserve(aSubIdVec.size());
        std::transform(
            aSubIdVec.begin(), aSubIdVec.end(),
            std::back_inserter(mSubIds),
            [this](const auto& aSubShapeId) {
                return aSubShapeId.subId();
            }
        );
    }

    SubShapeIdList() = default;
    virtual ~SubShapeIdList() = default;
    inline PartLabel root() const { return mParentLabel; }
    inline ShapeType shapeType() const { return mShapeType; }
    inline std::vector<int> subIdVec() const { return mSubIds; }
    inline std::vector<SubShapeId> subIds() const { 
        std::vector<SubShapeId> ids;
        ids.reserve(mSubIds.size());
        std::transform(
            mSubIds.begin(), mSubIds.end(),
            std::back_inserter(ids),
            [this](int id) {
                return SubShapeId(mParentLabel, mShapeType, id);
            }
        );

        return ids; 
    }

private:
    std::vector<int> mSubIds{};
    PartLabel mParentLabel{};
    ShapeType mShapeType = ShapeType::TopAbs_SOLID;
};
#endif