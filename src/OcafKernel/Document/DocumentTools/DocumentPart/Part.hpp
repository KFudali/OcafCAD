#ifndef Part_hpp
#define Part_hpp

#include <Standard_Handle.hxx>

#include "PartLabel.hpp"
#include "ShapeLabel.hpp"
#include "Shape.hpp"
#include "Location.hpp"
#include "ColorRGBA.hpp"

#include "PartSubShapeTool.hpp"
#include "PartShapeTool.hpp"
#include "PartAttributeTool.hpp"

class XCAFDoc_ShapeTool;
class Part {
    public:
    inline static ColorRGBA defaultPartColor = ColorRGBA();
    inline static std::string defaultPartName = "PartName";
    
    Part(const PartLabel& aPartLabel);
    virtual ~Part() = default;

    Shape shape() const;
    Location location() const;

    PartSubShapeTool& subShapes() const;    
    PartSubShapeTool& attributes() const;    

    protected:
    PartLabel mPartLabel;
    Handle(XCAFDoc_ShapeTool) mShapeTool;

    PartAttributeTool mAttributes;
    PartSubShapeTool mSubShapes;
    PartShapeTool mShapes;
};

#endif