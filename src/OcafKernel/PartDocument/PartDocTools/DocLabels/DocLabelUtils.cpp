#include "DocLabelUtils.hpp"
#include "RootAssemblyAttribute.hpp"

#include "XCAFDoc_ShapeTool.hxx"
#include "XCAFDoc_DocumentTool.hxx"

bool DocLabelUtils::isRootAssemblyLabel(TDF_Label aLabel) {
    return aLabel.IsAttribute(RootAssemblyAttribute::GetID());
}

bool DocLabelUtils::isPartLabel(TDF_Label aLabel) {
    if (aLabel.IsNull()){
        return false;
    }
    auto comp = XCAFDoc_ShapeTool::IsComponent(aLabel);
    auto shapeRef = XCAFDoc_ShapeTool::IsReference(aLabel);
    if (comp && shapeRef){
        return true;
    }
    return false;
}


bool DocLabelUtils::isPrototypeLabel(TDF_Label aLabel) {
    if (aLabel.IsNull()){
        return false;
    }
    auto shapeTool = XCAFDoc_DocumentTool::ShapeTool(aLabel.Root());
    auto isTopLevel = shapeTool->IsTopLevel(aLabel);
    auto isAssembly = shapeTool->IsAssembly(aLabel);
    auto isRoot = DocLabelUtils::isRootAssemblyLabel(aLabel);
    if ( isTopLevel && !isAssembly && !isRoot){
        return true;
    } else {
        return false;
    }
}