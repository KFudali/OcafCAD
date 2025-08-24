#ifndef PartAssemblyTool_hpp
#define PartAssemblyTool_hpp

#include "PartLabel.hpp"
#include "AbstractPartAssemblyTool.hpp"

#include <Standard_Handle.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>

class PartAssemblyTool : public AbstractPartAssemblyTool {
    public:
    PartAssemblyTool(PartLabel aPartLabel);

    bool isAssembly() const override;
    bool isComponent() const override;

    std::vector<PartLabel> childrenComponents() const override;
    PartLabel parentAssembly() const override;

    bool addComponent(PartLabel aPartLabel) override;
    bool removeComponent(PartLabel aPartLabel) override;

    private:

    TDF_Label parentLabel(TDF_Label aLabel) const;
    bool isRootAssembly(TDF_Label aLabel) const;
    bool isPrototype(TDF_Label aLabel) const;

    Handle(XCAFDoc_ShapeTool) mShapeTool;
    PartLabel mPartLabel;
};

#endif