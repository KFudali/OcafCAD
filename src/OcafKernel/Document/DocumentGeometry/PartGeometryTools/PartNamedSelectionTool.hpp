#ifndef PartNamedSelectionTool_hpp
#define PartNamedSelectionTool_hpp

#include <string>
#include <vector>
#include <Standard_Handle.hxx>
#include <TDF_Label.hxx>

#include "PartLabel.hpp"
#include "SubShapeId.hpp"
#include "GeometryNamedSelection.hpp"

class XCAFDoc_ShapeTool;
class PartNamedSelectionTool {
    public:
    PartNamedSelectionTool(const PartLabel& aPartLabel);

    std::vector<GeometryNamedSelection> namedSelections() const;
    TDF_Label namedSelectionTreeLabel() const;

    GeometryNamedSelection addNamedSelection(
        const SubShapeId& aSubShapeId, 
        const std::string& aName
    );
    bool removeNamedSelection(const GeometryNamedSelection& aNamedSelection);

    private:
    PartLabel mPartLabel;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};

#endif