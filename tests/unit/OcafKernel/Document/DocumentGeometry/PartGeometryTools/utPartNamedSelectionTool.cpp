#include <gmock/gmock.h>

#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>

#include "DocumentGeometryFixture.hpp"
#include "StubPartPrototypes.hpp"

#include "PartNamedSelectionTool.hpp"
#include "PartSubShapeTool.hpp"
using ::testing::UnorderedElementsAre;
using ::testing::Contains;
class PartNamedSelectionToolTest : public DocumentGeometryFixture {
    protected:
    void SetUp() {
        DocumentGeometryFixture::SetUp();
        auto cubeShapeLabel = geoDoc->addShape(cubePrototype);
        auto cubePartLabel = geoDoc->addPart(cubeShapeLabel, Location());
        shapeTool = XCAFDoc_DocumentTool::ShapeTool(cubePartLabel.label());

        TDF_Label subShapeLabel;
        auto subShapeTool = PartSubShapeTool(cubePartLabel);
        
        auto faces = subShapeTool.subShapesOfType(ShapeType::TopAbs_FACE);
        faceId = SubShapeId(
            cubePartLabel, ShapeType::TopAbs_FACE, faces.subIdVec()[0]
        );
        anotherFaceId = SubShapeId(
            cubePartLabel, ShapeType::TopAbs_FACE, faces.subIdVec()[1]
        );
        
        namedSelectionTool = std::make_unique<PartNamedSelectionTool>(cubePartLabel);
    }
    
    Shape cubePrototype = StubPartPrototypes::cube();
    Shape exampleFace;

    SubShapeId faceId;
    SubShapeId anotherFaceId;

    std::unique_ptr<PartNamedSelectionTool> namedSelectionTool;
    Handle(XCAFDoc_ShapeTool) shapeTool;
};

TEST_F(PartNamedSelectionToolTest, AddNamedSelectionCreatesSelectionOnProperLabel){
    std::string name("NamedSelectionHandle");
    auto namedSelection = namedSelectionTool->addNamedSelection(faceId, name);
    EXPECT_EQ(namedSelection.name(), name);
    EXPECT_EQ(faceId, namedSelection.namedShapeId());
}


TEST_F(PartNamedSelectionToolTest, AddedNamedSelectionsCanBeFetched)
{
    std::string name("NamedSelectionHandle");
    std::string anotherName("AnotherNamedSelection");

    auto namedSelection = namedSelectionTool->addNamedSelection(faceId, name);
    auto anotherNamedSelection = namedSelectionTool->addNamedSelection(
        anotherFaceId, anotherName
    );

    ASSERT_EQ(namedSelectionTool->namedSelections().size(), 2);
    EXPECT_THAT(
        namedSelectionTool->namedSelections(), 
        UnorderedElementsAre(namedSelection, anotherNamedSelection)
    );
}

TEST_F(PartNamedSelectionToolTest, AddedNamedSelectionsCanBeRemoved){
    std::string name("NamedSelectionHandle");
    std::string anotherName("AnotherNamedSelection");
    auto namedSelection = namedSelectionTool->addNamedSelection(faceId, name);
    auto anotherNamedSelection = namedSelectionTool->addNamedSelection(
        anotherFaceId, anotherName
    );
    namedSelectionTool->removeNamedSelection(namedSelection);
    ASSERT_EQ(namedSelectionTool->namedSelections().size(), 1);
    EXPECT_EQ(namedSelectionTool->namedSelections()[0], anotherNamedSelection);
}