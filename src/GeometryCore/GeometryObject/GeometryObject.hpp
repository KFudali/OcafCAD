#ifndef GeometryObject_hpp
#define GeometryObject_hpp

#include "Part.hpp"
#include "ShapeIds.hpp"

class GeometryObject {
    public:
    GeometryObject(
        const PartLabel& aSourcePartLabel
    ) : mSourcePart(Part(aSourcePartLabel)) {}
    
    inline PartPrototype rootShape() const {return mSourcePart.prototype();};

    SubShapeIdList points() const;
    SubShapeIdList edges() const;
    SubShapeIdList faces() const;
    SubShapeIdList volumes() const;

    PartPrototype getSubShape(const SubShapeId& aShapeId) const;
    PartPrototype getTypedSubShape(const TypedSubShapeId& aShapeId) const;
    SubShapeId getSubShapeId(const PartPrototype& aPartPrototype) const;

    private:
    Part mSourcePart;
};

#endif