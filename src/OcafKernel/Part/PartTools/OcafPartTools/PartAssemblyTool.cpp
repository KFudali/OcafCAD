#include "PartAssemblyTool.hpp"

PartAssemblyTool::PartAssemblyTool(PartLabel aPartLabel) 
  : mPartLabel(aPartLabel),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aPartLabel.label())) {}

bool PartAssemblyTool::isAssembly() const {
   return mShapeTool->IsAssembly(mPartLabel.label()); 
};
bool PartAssemblyTool::isComponent() const {
    return true;
}
std::vector<PartLabel> PartAssemblyTool::childrenComponents() const {
    return std::vector<PartLabel>();    
};

PartLabel PartAssemblyTool::parentAssembly() const {
    return mPartLabel;
};

bool PartAssemblyTool::addComponent(PartLabel aPartLabel) {return false;};
bool PartAssemblyTool::removeComponent(PartLabel aPartLabel) {return false;};