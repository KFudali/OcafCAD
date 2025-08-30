#include "PartDocument.hpp"
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XmlXCAFDrivers.hxx>
#include <XmlDrivers.hxx>
#include <PCDM_StoreStatus.hxx>
PartDocument::PartDocument(Handle(XCAFApp_Application) aXCAFApp) : mApp(aXCAFApp) {
    mApp->NewDocument("XmlXCAF", mDoc);
    mApp->InitDocument(mDoc);
    mShapeTool = XCAFDoc_DocumentTool::ShapeTool(mDoc->Main());
    mShapeTool->SetAutoNaming(false);
    mRootAssembly = std::make_unique<RootAssembly>(mDoc);
    mPrototypeRegistry = std::make_unique<PrototypeRegistry>(mDoc);
} 

bool PartDocument::save(const std::string& aFilePath) const {
    TCollection_ExtendedString xmlPath(aFilePath.c_str());
    XmlXCAFDrivers::DefineFormat(mApp);
    XmlDrivers::DefineFormat(mApp);
    if (mApp->SaveAs(mDoc, xmlPath) == PCDM_StoreStatus::PCDM_SS_OK) {
        return true;
    }
    return false;
}

PartLabel PartDocument::addPart(PrototypeLabel aPrototype, Location aLocation){
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

PartLabel PartDocument::addEmptyPart() {
    return mRootAssembly->addEmptyPart();
}


PartLabel PartDocument::addEmptyAssembly() {
    return mRootAssembly->addEmptyAssembly();
}