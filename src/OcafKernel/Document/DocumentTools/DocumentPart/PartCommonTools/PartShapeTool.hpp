#ifndef PartShapeTool_hpp
#define PartShapeTool_hpp

#include <Standard_Handle.hxx>

#include "PartLabel.hpp"
#include "Shape.hpp"
#include "Location.hpp"

class XCAFDoc_ShapeTool;
class PartShapeTool {
    public:
    PartShapeTool(const PartLabel& aPartLabel);
    inline PartLabel label() const {return mPartLabel;}

    Shape shape() const;
    Location location() const;
    inline Handle(XCAFDoc_ShapeTool) occShapeTool() {return mShapeTool;};

    private:
    PartLabel mPartLabel;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};

#endif