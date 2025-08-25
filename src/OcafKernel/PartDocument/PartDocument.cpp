#include "PartDocument.hpp"
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>


PartDocument::PartDocument(Handle(XCAFApp_Application) aXCAFApp) : mApp(aXCAFApp) {
    mApp->NewDocument("XCAFXml", mDoc);
    mShapeTool = XCAFDoc_DocumentTool::ShapeTool(mDoc->Main());
    mShapeTool->SetAutoNaming(false);
    mRootAssembly = std::make_unique<RootAssembly>(mDoc);
    mPrototypeRegistry = std::make_unique<PrototypeRegistry>(mDoc);
} 

Part PartDocument::addPart(PrototypeLabel aPrototype, Location aLocation){
    return mRootAssembly->addPart(aPrototype, aLocation);
}

PrototypeLabel PartDocument::addPrototype(PartPrototype aPrototype) {
    return mPrototypeRegistry->addPrototype(aPrototype);
}

std::vector<PrototypeLabel> PartDocument::prototypes() const {
    return mPrototypeRegistry->prototypeList();
}

std::vector<PartLabel> PartDocument::freeParts() const {
    return mRootAssembly->freeParts();
}