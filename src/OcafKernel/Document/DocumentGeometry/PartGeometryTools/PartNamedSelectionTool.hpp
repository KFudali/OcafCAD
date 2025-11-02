#ifndef PartNamedSelectionTool_hpp
#define PartNamedSelectionTool_hpp

#include <string>
#include <vector>
#include <Standard_Handle.hxx>
#include <TDF_Label.hxx>

#include "PartLabel.hpp"
#include "SubShapeId.hpp"
#include "NamedSelection.hpp"

class XCAFDoc_ShapeTool;
class PartNamedSelectionTool {
    public:
    PartNamedSelectionTool(const PartLabel& aPartLabel);

    std::vector<NamedSelection> namedSelections() const;

    NamedSelection addNamedSelection(
        const SubShapeId& aSubShapeId, 
        const std::string& aName
    );

    bool removeNamedSelection(const NamedSelection& aNamedSelection);

    private:
    TDF_Label namedSelectionTreeLabel() const;
    PartLabel mPartLabel;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};

#endif