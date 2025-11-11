#include <gtest/gtest.h>

#include "DocumentGeometryFixture.hpp"
#include "PartSubShapeNamedSelection.hpp"

#include <XCAFApp_Application.hxx>
#include <TDocStd_Document.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelSequence.hxx>
#include <TopExp.hxx>
#include <unordered_set>

#include <gtest/gtest.h>
#include "PartSubShapeNamedSelection.hpp"

class PartSubShapeNamedSelectionTest : public DocumentGeometryFixture {
protected:
    void SetUp() override {
        DocumentGeometryFixture::SetUp();
        cubeShapeLabel = geoDoc->addShape(cubeShape);
        cubePartLabel = geoDoc->addPart(cubeShapeLabel, Location());
        
        shapeTool = XCAFDoc_DocumentTool::ShapeTool(cubeShapeLabel.label().Root());
        subShapeTool = std::make_unique<PartSubShapeTool>(cubePartLabel);

        TopExp::MapShapes(cubeShape, ShapeType::TopAbs_FACE, subFaces);
        shapeTool->AddSubShape(cubeShapeLabel.label(), subFaces(1), faceLabel_1);
        shapeTool->AddSubShape(cubeShapeLabel.label(), subFaces(2), faceLabel_2);
        faceSeq.Append(faceLabel_1);       
        faceSeq.Append(faceLabel_2);       

    }

    Shape cubeShape = StubPartPrototypes::cube();
    ShapeLabel cubeShapeLabel;
    PartLabel cubePartLabel;
    TopTools_IndexedMapOfShape subFaces;

    Shape face_1;
    Shape face_2;

    TDF_Label faceLabel_1;
    TDF_Label faceLabel_2;
    
    TDF_LabelSequence faceSeq;

    std::unique_ptr<PartSubShapeTool> subShapeTool;
    Handle(XCAFDoc_ShapeTool) shapeTool;
};


TEST_F(PartSubShapeNamedSelectionTest, rename) {
    auto anyParent = cubeShapeLabel.label().NewChild();
    std::string name =  "name";
    std::string newName =  "newName";
    PartSubShapeNamedSelection selection(cubePartLabel, anyParent, faceSeq, name);
    EXPECT_EQ(selection.name(), name);
    selection.rename(newName);
    EXPECT_EQ(selection.name(), newName);
}