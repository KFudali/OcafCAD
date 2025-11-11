#ifndef PartNamedSelectionTool_hpp
#define PartNamedSelectionTool_hpp

#include <string>
#include <vector>
#include <Standard_Handle.hxx>
#include <TDF_Label.hxx>

#include "PartLabel.hpp"
#include "SubShapeIdList.hpp"
#include "SubShapeId.hpp"
#include "PartSubShapeNamedSelection.hpp"

class XCAFDoc_ShapeTool;
class PartNamedSelectionTool {
    public:
    PartNamedSelectionTool(const PartLabel& aPartLabel);
    
    std::vector<PartSubShapeNamedSelection> selections() const;
    PartSubShapeNamedSelection addSelection(
        const SubShapeIdList& aSubShapeIdList, 
        const std::string& aName
    );
    bool removeSelection(PartSubShapeNamedSelection& aNamedSelection);
    
    private:
    TDF_Label namedSelectionTreeLabel() const;
    PartLabel mPartLabel;
    PartSubShapeTool mSubShapeTool;
};

#endif