#ifndef PartSubShapeTool_hpp
#define PartSubShapeTool_hpp

#include "PartLabel.hpp"
#include "SubShapeId.hpp"
#include "SubShapeIdList.hpp"
#include "PartPrototype.hpp"
#include "ShapeType.hpp"

#include <XCAFDoc_ShapeTool.hxx>
#include <Standard_Handle.hxx>
#include <XCAFDoc_DocumentTool.hxx>

class PartSubShapeTool {
    public:
    PartSubShapeTool(const PartLabel& aPartLabel);
    virtual ~PartSubShapeTool() = default;

    bool subShapeIdValid(const SubShapeId& aSubShapeId) const;
    SubShapeId subShapeId(const PartPrototype& aPartPrototype) const;
    PartPrototype subShape(const SubShapeId& aSubShapeId) const;

    SubShapeIdList subShapesOfType(const ShapeType& aShapeType) const;

    private:
    PartLabel mPartLabel;
    Handle(XCAFDoc_ShapeTool) mShapeTool;

};

#endif