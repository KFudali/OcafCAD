#ifndef Part_hpp
#define Part_hpp

#include <string>


#include "PartLabel.hpp"

#include "Shape.hpp"
#include "Location.hpp"
#include "ColorRGBA.hpp"


#include "PartShapeTool.hpp"
#include "PartSubShapeTool.hpp"
#include "PartAssemblyTool.hpp"
#include "PartAttributeTool.hpp"

class Part {
    public:
    inline static std::string defaultName = "DefaultPartName";
    inline static ColorRGBA defaultColor = ColorRGBA{0.5, 0.5, 0.5, 1.0};
    
    Part(const PartLabel& aPartLabel);
    ~Part() = default;

    inline PartLabel label() const {return mPartLabel;}

    inline Shape shape() const {return mShapeTool.shape(); }
    inline Location location() const {return mShapeTool.location(); }

    inline bool isAssembly() const {return mAssemblyTool.isAssembly();};
    inline bool isComponent() const {return mAssemblyTool.isComponent();};    

    inline PartSubShapeTool& subShapes() {return mSubShapeTool;} 
    inline PartAssemblyTool& assembly() {return mAssemblyTool;} 
    inline PartAttributeTool& attributes() {return mAttributeTool;} 

    private:
    PartLabel mPartLabel;
    PartShapeTool mShapeTool;
    PartSubShapeTool mSubShapeTool;
    PartAssemblyTool mAssemblyTool;
    PartAttributeTool mAttributeTool;
};

#endif