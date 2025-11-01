#ifndef PartSubShapeTool_hpp
#define PartSubShapeTool_hpp

#include <Standard_Handle.hxx>

#include "PartLabel.hpp"

#include "SubShapeId.hpp"
#include "SubShapeIdList.hpp"
#include "Shape.hpp"
#include "Location.hpp"

class XCAFDoc_ShapeTool;
class PartSubShapeTool {
    public:
    PartSubShapeTool(const PartLabel& aPartLabel);

    bool subShapeIdValid(const SubShapeId& aSubShapeId) const;
    SubShapeId subShapeId(const Shape& aPartPrototype) const;
    Shape subShape(const SubShapeId& aSubShapeId) const;
    SubShapeIdList subShapesOfType(const ShapeType& aShapeType) const;

    private:
    PartLabel mPartLabel;
    Handle(XCAFDoc_ShapeTool) mShapeTool;

};

#endif
