#include <gmock/gmock.h>

#include "DocumentGeometryFixture.hpp"
#include "StubPartPrototypes.hpp"

#include "PartSubShapeTool.hpp"

#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp.hxx>

class PartSubShapeToolTest : public DocumentGeometryFixture {
    protected:
    void SetUp() {
        DocumentGeometryFixture::SetUp();
        cubeShapeLabel = geoDoc->addShape(cubeShape);
        cubePartLabel = geoDoc->addPart(cubeShapeLabel, Location());
        subShapeTool = std::make_unique<PartSubShapeTool>(cubePartLabel);
    }
    Shape cubeShape = StubPartPrototypes::cube();
    ShapeLabel cubeShapeLabel;
    PartLabel cubePartLabel;
    std::unique_ptr<PartSubShapeTool> subShapeTool;
};

TEST_F(PartSubShapeToolTest, SubShapeIdValidReturnsTrueForValidId) {
    SubShapeId validId(cubePartLabel, ShapeType::TopAbs_FACE, 3);
    EXPECT_TRUE(subShapeTool->subShapeIdValid(validId));
}

TEST_F(PartSubShapeToolTest, SubShapeIdValidReturnsFalseForInvalidId) {
    SubShapeId invalidSubId(cubePartLabel, ShapeType::TopAbs_FACE, 7);
    EXPECT_FALSE(subShapeTool->subShapeIdValid(invalidSubId));

    SubShapeId invalidPartLabel(PartLabel(), ShapeType::TopAbs_FACE, 1);
    EXPECT_FALSE(subShapeTool->subShapeIdValid(invalidPartLabel));
}

TEST_F(PartSubShapeToolTest, SubShapesOfTypeReturnsExpectedFaceCountForCube) {
    auto faceList = subShapeTool->subShapesOfType(ShapeType::TopAbs_FACE);
    EXPECT_EQ(faceList.subIds().size(), 6);
    EXPECT_EQ(faceList.shapeType(), ShapeType::TopAbs_FACE);
    EXPECT_EQ(faceList.root(), cubePartLabel);
}

TEST_F(PartSubShapeToolTest, SubShape_ReturnsCorrectShapeType) {
    auto faceList = subShapeTool->subShapesOfType(ShapeType::TopAbs_FACE);
    ASSERT_FALSE(faceList.subIds().empty());

    Shape faceShape = subShapeTool->subShape(
        SubShapeId(
            faceList.root(), 
            ShapeType::TopAbs_FACE, 
            faceList.subIds().front()
        )
    );

    ASSERT_FALSE(faceShape.IsNull());
    EXPECT_EQ(faceShape.ShapeType(), TopAbs_FACE);
}