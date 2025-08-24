#include "RootAssembly.hpp"

RootAssembly::RootAssembly(Handle(TDocStd_Document) aDoc)
 :  mDoc(aDoc),
    mShapeTool(XCAFDoc_DocumentTool::ShapeTool(aDoc->Main()))
{
    TDF_Label label = mShapeTool->NewShape();
    mLabel = DocLabel(label);
}

void RootAssembly::clear(){}; 


PartLabel RootAssembly::addPart(
    PrototypeLabel aPrototypeLabel, 
    Location aLocation
){
    TDF_Label label = mShapeTool->AddComponent(
        mLabel.label(),
        aPrototypeLabel.label(),
        aLocation
    );
    return PartLabel(label);
};

void RootAssembly::removePart(PartLabel aPartLabel){}