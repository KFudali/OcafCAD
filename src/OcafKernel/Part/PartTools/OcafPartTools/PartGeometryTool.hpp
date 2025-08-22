#ifndef PartGeometryTool_hpp
#define PartGeometryTool_hpp

#include "PartLabel.hpp"
#include "AbstractPartGeometryTool.hpp"

#include <Standard_Handle.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>

class PartGeometryTool : public AbstractPartGeometryTool {
    public:
    PartGeometryTool(PartLabel aPartLabel);

    PartPrototype prototype() const override;
    Location location() const override;

    bool setPrototype(PartPrototype aPrototype) override;
    bool setLocation(Location aLocation) override;

    // bool scale(double scaleFactor, Location aScaleCenter) override;
    // bool scale(double scaleFactor) override;

    private:
    PartLabel mLabel;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};

#endif