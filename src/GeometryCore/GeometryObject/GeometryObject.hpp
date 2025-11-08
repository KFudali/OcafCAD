#ifndef GeometryObject_hpp
#define GeometryObject_hpp

#include "Part.hpp"
#include "PartNamedSelectionTool.hpp"

class GeometryObject {
    public:
    GeometryObject(const PartLabel& aSourcePartLabel);
   
    inline Shape rootShape() const {
        return mSourcePart.shape().Located(mSourcePart.location());
    };
    inline PartSubShapeTool& subShapes() {return mSourcePart.subShapes();} 
    inline PartNamedSelectionTool& namedSelections() {
        return mNamedSelectionTool;
    }
    
    private:
    Part mSourcePart;
    PartNamedSelectionTool mNamedSelectionTool;
};

#endif