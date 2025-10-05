#include "DocumentGeometry.hpp"
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XmlXCAFDrivers.hxx>
#include <XmlDrivers.hxx>
#include <PCDM_StoreStatus.hxx>

DocumentGeometry::DocumentGeometry(Handle(TDocStd_Document) aDoc) : mDoc(aDoc) {
    mShapeTool->SetAutoNaming(false);
    mRootAssembly = std::make_unique<RootAssembly>(mDoc);
    mPrototypeRegistry = std::make_unique<PrototypeRegistry>(mDoc);
} 

// bool DocumentGeometry::save(const std::string& aFilePath) const {
//     TCollection_ExtendedString xmlPath(aFilePath.c_str());
//     XmlXCAFDrivers::DefineFormat(mApp);
//     XmlDrivers::DefineFormat(mApp);
//     if (mApp->SaveAs(mDoc, xmlPath) == PCDM_StoreStatus::PCDM_SS_OK) {
//         return true;
//     }
//     return false;
// }

PartLabel DocumentGeometry::addPart(PrototypeLabel aPrototype, Location aLocation){
    return mRootAssembly->addPart(aPrototype, aLocation);
}

PrototypeLabel DocumentGeometry::addPrototype(PartPrototype aPrototype) {
    return mPrototypeRegistry->addPrototype(aPrototype);
}

PrototypeLabel DocumentGeometry::addAssemblyPrototype(PartPrototype aPrototype) {
    return mPrototypeRegistry->addAssemblyPrototype(aPrototype);
}

std::vector<PrototypeLabel> DocumentGeometry::prototypes() const {
    return mPrototypeRegistry->prototypeList();
}

std::vector<PartLabel> DocumentGeometry::topLevelParts() const {
    return mRootAssembly->topLevelParts();
}

std::vector<PartLabel> DocumentGeometry::freeParts() const {
    return mRootAssembly->freeParts();
}

PartLabel DocumentGeometry::addEmptyPart() {
    return mRootAssembly->addEmptyPart();
}

PartLabel DocumentGeometry::addEmptyAssembly() {
    return mRootAssembly->addEmptyAssembly();
}