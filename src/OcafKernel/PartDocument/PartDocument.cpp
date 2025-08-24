#include "PartDocument.hpp"
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>


PartDocument::PartDocument(Handle(XCAFApp_Application) aXCAFApp) : mApp(aXCAFApp) {
    mApp->NewDocument("XCAFXml", mDoc);
    mShapeTool = XCAFDoc_DocumentTool::ShapeTool(mDoc->Main());
    mShapeTool->SetAutoNaming(false);
    mRootAssembly = std::make_unique<RootAssembly>(mDoc);
} 

Part PartDocument::addPart(PrototypeLabel aPrototype, Location aLocation){
    return mRootAssembly->addPart(aPrototype, aLocation);
}

PrototypeLabel PartDocument::addPrototype(PartPrototype aPrototype) {
    auto label = mShapeTool->AddShape(aPrototype, false, false); 
    return PrototypeLabel(label);
}

std::vector<PrototypeLabel> PartDocument::prototypes() const {
    return {};
}

std::vector<PartLabel> PartDocument::freeParts() const {
    return {};
}