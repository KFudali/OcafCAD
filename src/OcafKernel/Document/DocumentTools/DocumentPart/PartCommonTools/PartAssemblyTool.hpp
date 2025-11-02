#ifndef PartAssemblyTool_hpp
#define PartAssemblyTool_hpp

#include <Standard_Handle.hxx>
#include <vector>

#include "PartLabel.hpp"
#include "ShapeLabel.hpp"
#include "Location.hpp"

class XCAFDoc_ShapeTool;
class PartAssemblyTool {
    public:
    PartAssemblyTool(const PartLabel& aPartLabel);

    inline PartLabel label() const {return mPartLabel;}

    bool expandToAssembly();
    PartLabel addComponent(PartLabel aPartLabel, Location aLocation);
    PartLabel addComponent(ShapeLabel aPartLabel, Location aLocation);
    PartLabel addEmptyComponent();
    bool removeComponent(PartLabel aPartLabel);

    std::vector<PartLabel> childrenComponents() const;
    PartLabel parentAssembly() const;

    bool isAssembly() const;
    bool isComponent() const;    

    private:
    PartLabel mPartLabel;
    Handle(XCAFDoc_ShapeTool) mShapeTool;

};

#endif