#include "PrototypeRegistry.hpp"
#include "RootAssembly.hpp"

PrototypeRegistry::PrototypeRegistry(Handle(TDocStd_Document) aDoc) : mDoc(aDoc) {
    mShapeTool = XCAFDoc_DocumentTool::ShapeTool(mDoc->Main());
}

PrototypeLabel PrototypeRegistry::addPrototype(PartPrototype aShape){
    TDF_Label aLabel = mShapeTool->AddShape(aShape, false, false);
    return PrototypeLabel(aLabel);
};

bool PrototypeRegistry::removePrototype(PrototypeLabel aPrototypeLabel) {
    if (!aPrototypeLabel.isValid()) {
        return false;
    }
    return mShapeTool->RemoveShape(aPrototypeLabel.label());
}

std::vector<PrototypeLabel> PrototypeRegistry::prototypeList() const {
    std::vector<PrototypeLabel> prototypes;
    TDF_LabelSequence labels;
    mShapeTool->GetFreeShapes(labels);

    for (auto label : labels) {
        if (RootAssembly::isRootAssembly(label)) {
            continue;
        }
        prototypes.push_back(PrototypeLabel(label));
    }
    return prototypes;
}