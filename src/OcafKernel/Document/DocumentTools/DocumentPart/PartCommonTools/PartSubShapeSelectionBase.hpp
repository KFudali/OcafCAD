#ifndef PartSubShapeSelectionBase_hpp
#define PartSubShapeSelectionBase_hpp

#include "RefTreeLabel.hpp"
#include "PartSubShapeTool.hpp"
#include "SubShapeIdList.hpp"
#include "SubShapeId.hpp"


class PartSubShapeSelectionBase {
public:
    virtual ~PartSubShapeSelectionBase() = default;

    inline RefTreeLabel* const label() {return mRefTreeLabel;}
    SubShapeIdList ids() const;
    void clear();
    bool append(const SubShapeId& aSubShapeId);
    bool remove(const SubShapeId& aSubShapeId);

protected:
    PartSubShapeSelectionBase(
        const PartLabel& aPartLabel, 
        RefTreeLabel* aRefTreeLabel
    ) : mSubShapeTool(aPartLabel), mRefTreeLabel(aRefTreeLabel){}

    RefTreeLabel* const mRefTreeLabel;
    PartSubShapeTool mSubShapeTool;
};

#endif

