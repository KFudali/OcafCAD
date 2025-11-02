#include "DocumentGeometry.hpp"
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XmlXCAFDrivers.hxx>
#include <XmlDrivers.hxx>
#include <PCDM_StoreStatus.hxx>

DocumentGeometry::DocumentGeometry(Handle(TDocStd_Document) aDoc) : mDoc(aDoc) {
    mShapeTool->SetAutoNaming(false);
    mRootAssembly = std::make_unique<RootAssembly>(mDoc);
    mPrototypeRegistry = std::make_unique<ShapeRegistry>(mDoc);
} 

PartLabel DocumentGeometry::addPart(ShapeLabel aPrototype, Location aLocation){
    return mRootAssembly->addPart(aPrototype, aLocation);
}

ShapeLabel DocumentGeometry::addShape(Shape aPrototype) {
    return mPrototypeRegistry->addShape(aPrototype);
}

ShapeLabel DocumentGeometry::addAssemblyPrototype(Shape aPrototype) {
    return mPrototypeRegistry->addAssemblyPrototype(aPrototype);
}

std::vector<ShapeLabel> DocumentGeometry::prototypes() const {
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