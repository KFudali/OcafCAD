#include "Part.hpp"

Part::Part(
    const PartLabel& aPartLabel
) : mPartLabel(aPartLabel),
    mShapeTool(aPartLabel),
    mSubShapeTool(aPartLabel),
    mAssemblyTool(aPartLabel),
    mAttributeTool(aPartLabel){
        if (!mAttributeTool.hasColor()){
            mAttributeTool.setColor(Part::defaultColor);
        }
        if (!mAttributeTool.hasName()){
            mAttributeTool.setName(Part::defaultName);
        }
    }