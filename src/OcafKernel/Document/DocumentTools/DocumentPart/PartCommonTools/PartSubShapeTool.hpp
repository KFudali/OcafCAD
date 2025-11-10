#ifndef PartSubShapeTool_hpp
#define PartSubShapeTool_hpp

#include <Standard_Handle.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TDF_LabelSequence.hxx>

#include "PartLabel.hpp"
#include "SubShapeLabel.hpp"

#include "SubShapeId.hpp"
#include "SubShapeIdList.hpp"
#include "Shape.hpp"
#include "ShapeType.hpp"
#include "Location.hpp"

class XCAFDoc_ShapeTool;
class PartSubShapeTool {
    public:
    PartSubShapeTool(const PartLabel& aPartLabel);
    inline PartLabel label() const {return mPartLabel;}
    
    bool subShapeIdValid(const SubShapeId& aSubShapeId) const;
    SubShapeId subShapeId(const Shape& aPartShape) const;
    SubShapeId subShapeId(const SubShapeLabel& aPartShape) const;
    Shape subShape(const SubShapeId& aSubShapeId) const;
    SubShapeLabel subShapeLabel(const SubShapeId& aSubShapeId) const;
    SubShapeLabel subShapeLabel(const Shape& aSubShape) const;
    
    TDF_LabelSequence subShapeLabels(const SubShapeIdList& aSubShapeId) const;
    SubShapeIdList subShapeIds(const TDF_LabelSequence& aSubShapeLabels) const;

    SubShapeIdList subShapesOfType(const ShapeType& aShapeType) const;

    private:
    TopTools_IndexedMapOfShape subShapeMap(const ShapeType& aShapeType) const;
    PartLabel mPartLabel;
    Handle(XCAFDoc_ShapeTool) mShapeTool;

};

#endif
