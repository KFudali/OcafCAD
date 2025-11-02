#include <gmock/gmock.h>

#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>

#include "DocumentGeometryFixture.hpp"
#include "StubPartPrototypes.hpp"

#include "NamedSelectionLabel.hpp"
#include "PartSubShapeTool.hpp"

class NamedSelectionLabelTest : public DocumentGeometryFixture {
    protected:
    void SetUp() {
        DocumentGeometryFixture::SetUp();
        cubeShapeLabel = geoDoc->addShape(cubePrototype);
        cubePartLabel = geoDoc->addPart(cubeShapeLabel, Location());
        shapeTool = XCAFDoc_DocumentTool::ShapeTool(cubePartLabel.label());

        TDF_Label subShapeLabel;
        auto subShapeTool = PartSubShapeTool(cubePartLabel);
        
        auto faces = subShapeTool.subShapesOfType(ShapeType::TopAbs_FACE);
        auto faceId = SubShapeId(
            cubePartLabel, 
            ShapeType::TopAbs_FACE, 
            faces.subIds().front()
        );
        auto exampleFace = subShapeTool.subShape(faceId);
        ASSERT_FALSE(exampleFace.IsNull());
        subShapeLabel = shapeTool->AddSubShape(
            cubeShapeLabel.label(), exampleFace
        );

    }
    Shape cubePrototype = StubPartPrototypes::cube();
    ShapeLabel cubeShapeLabel;
    PartLabel cubePartLabel;
    TDF_Label subShapeLabel;
    Handle(XCAFDoc_ShapeTool) shapeTool;
};

TEST_F(NamedSelectionLabelTest, NamedSelectionCanBeCreatedOnCubeFace){
    std::string name("NamedSelectionLabel");
    NamedSelectionLabel selection(
        cubePartLabel.label(), 
        subShapeLabel, 
        name 
    );
    ASSERT_EQ(selection.name(), name);
}

TEST_F(NamedSelectionLabelTest, CreatingNamedSelectionTwiceJustRenames){
    std::string name("NamedSelectionLabel");
    std::string anotherName("AnotherNamedSelection");
    NamedSelectionLabel selection(
        cubePartLabel.label(), 
        subShapeLabel, 
        name 
    );
    NamedSelectionLabel anotherSelection(
        cubePartLabel.label(), 
        subShapeLabel, 
        anotherName 
    );
    EXPECT_TRUE(selection.label().IsEqual(anotherSelection.label()));
    EXPECT_EQ(selection.name(), anotherName);
    EXPECT_EQ(anotherSelection.name(), anotherName);
}

TEST_F(NamedSelectionLabelTest, NamedSelectionCanBeRenamed){
    std::string name("NamedSelectionLabel");
    std::string newName("NamedSelectionLabel");
    NamedSelectionLabel selection(
        cubePartLabel.label(), 
        subShapeLabel, 
        name 
    );

    selection.rename(newName);
    ASSERT_EQ(selection.name(), newName);
}