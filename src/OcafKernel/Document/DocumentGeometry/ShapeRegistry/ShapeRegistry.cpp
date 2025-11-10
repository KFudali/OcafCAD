#include "ShapeRegistry.hpp"

ShapeRegistry::ShapeRegistry(Handle(TDocStd_Document) aDoc) : mDoc(aDoc) {
    mShapeTool = XCAFDoc_DocumentTool::ShapeTool(mDoc->Main());
}

ShapeLabel ShapeRegistry::addShape(Shape aShape){
    TDF_Label label = mShapeTool->FindShape(aShape, false);
    if (label.IsNull()){
        label = mShapeTool->AddShape(aShape, false, false);
    }
    return ShapeLabel(label);
};

ShapeLabel ShapeRegistry::addAssemblyPrototype(Shape aShape){
    TDF_Label label = mShapeTool->FindShape(aShape, false);
    if (label.IsNull()){
        label = mShapeTool->NewShape();
    }
    return ShapeLabel(label);
};

bool ShapeRegistry::removePrototype(ShapeLabel aPrototypeLabel) {
    if (!aPrototypeLabel.isValid()) {
        return false;
    }
    return mShapeTool->RemoveShape(aPrototypeLabel.label());
}

std::vector<ShapeLabel> ShapeRegistry::prototypeList() const {
    std::vector<ShapeLabel> prototypes;
    TDF_LabelSequence labels;
    mShapeTool->GetShapes(labels);

    for (auto label : labels) {
        if (ShapeLabel::isShapeLabel(label)){
            prototypes.push_back(ShapeLabel(label));
        }
    }
    return prototypes;
}