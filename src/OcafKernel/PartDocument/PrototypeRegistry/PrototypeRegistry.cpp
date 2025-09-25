#include "PrototypeRegistry.hpp"
#include "RootAssembly.hpp"

PrototypeRegistry::PrototypeRegistry(Handle(TDocStd_Document) aDoc) : mDoc(aDoc) {
    mShapeTool = XCAFDoc_DocumentTool::ShapeTool(mDoc->Main());
}

PrototypeLabel PrototypeRegistry::addPrototype(PartPrototype aShape){
    TDF_Label label = mShapeTool->FindShape(aShape, false);
    if (label.IsNull()){
        label = mShapeTool->AddShape(aShape, false, false);
    }
    return PrototypeLabel(label);
};

PrototypeLabel PrototypeRegistry::addAssemblyPrototype(PartPrototype aShape){
    TDF_Label label = mShapeTool->FindShape(aShape, false);
    if (label.IsNull()){
        label = mShapeTool->NewShape();
    }
    return PrototypeLabel(label);
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
    mShapeTool->GetShapes(labels);

    for (auto label : labels) {
        if (PrototypeLabel::isPrototypeLabel(label)){
            prototypes.push_back(PrototypeLabel(label));
        }
    }
    return prototypes;
}