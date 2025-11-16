#ifndef GeometryObject_hpp
#define GeometryObject_hpp

#include "Part.hpp"
#include "PartNamedSelectionTool.hpp"
#include "PartSubShapeTool.hpp"

class GeometryObject {
    public:
    GeometryObject(const PartLabel& aSourcePartLabel);
   
    inline Shape rootShape() const {
        return mSourcePart.shape().Located(mSourcePart.location());
    };
    inline PartSubShapeTool& subShapes() {return mSubShapes;} 
    inline PartNamedSelectionTool& namedSelections() {
        return mNamedSelectionTool;
    }
    
    private:
    Part mSourcePart;
    PartSubShapeTool mSubShapes;
    PartNamedSelectionTool mNamedSelectionTool;
};

#endif