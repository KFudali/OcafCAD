#ifndef Part_hpp
#define Part_hpp

#include <Standard_Handle.hxx>

#include "PartLabel.hpp"
#include "PrototypeLabel.hpp"
#include "PartPrototype.hpp"
#include "Location.hpp"

#include "PartAttributeTool.hpp"
#include "PartSubShapeTool.hpp"

class XCAFDoc_ShapeTool;
class Part {
    public:
    inline static ColorRGBA defaultPartColor = ColorRGBA();
    inline static std::string defaultPartName = "PartName";
    
    Part(const PartLabel& aPartLabel);
    
    virtual ~Part() = default;

    inline PartLabel partLabel() const {return mPartLabel;}; 
    PartPrototype prototype() const;
    Location location() const;

    inline PartAttributeTool& attributes() {return mAttributes;};
    inline PartSubShapeTool& subShapes() {return mSubShapes;};

    bool isAssembly() const;
    bool isComponent() const;    

    std::vector<PartLabel> childrenComponents() const;
    PartLabel parentAssembly() const;

    protected:
    PartLabel mPartLabel;
    PartAttributeTool mAttributes;
    PartSubShapeTool mSubShapes;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};

#endif