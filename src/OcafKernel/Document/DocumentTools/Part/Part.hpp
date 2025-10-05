#ifndef Part_hpp
#define Part_hpp

#include <Standard_Handle.hxx>

#include "PartLabel.hpp"
#include "PtototypeLabel.hpp"

#include "PartAttributeTool.hpp"

class XCAFDoc_ShapeTool;
class Part {
    public:
    inline static ColorRGBA defaultPartColor = ColorRGBA();
    inline static std::string defaultPartName = "PartName";
    
    Part(const PartLabel& aPartLabel);
    
    virtual ~Part() = default;
    Part(const Part& other);

    inline PartLabel partLabel() const {return mPartLabel;}; 
    PartPrototype prototype() const;
    Location location() const;

    inline PartAttributeTool& attributes() const {return mAttributes;};

    bool isAssembly() const;
    bool isComponent() const;    

    std::vector<PartLabel> childrenComponents() const;
    PartLabel parentAssembly() const;

    protected:
    PartLabel mPartLabel;
    PartAttributeTool mAttributes;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};

#endif