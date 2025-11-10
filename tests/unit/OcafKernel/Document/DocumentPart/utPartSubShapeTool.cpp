#include <gmock/gmock.h>

#include "DocumentGeometryFixture.hpp"
#include "StubPartPrototypes.hpp"

#include "PartSubShapeTool.hpp"

#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp.hxx>

class PartSubShapeToolTest : public DocumentGeometryFixture {
protected:
    void SetUp() override {
        DocumentGeometryFixture::SetUp();
        cubeShapeLabel = geoDoc->addShape(cubeShape);
        shapeTool = XCAFDoc_DocumentTool::ShapeTool(cubeShapeLabel.label().Root());
        cubePartLabel = geoDoc->addPart(cubeShapeLabel, Location());
        subShapeTool = std::make_unique<PartSubShapeTool>(cubePartLabel);
        TopExp::MapShapes(cubeShape, ShapeType::TopAbs_FACE, subFaces);
    }

    Shape cubeShape = StubPartPrototypes::cube();
    ShapeLabel cubeShapeLabel;
    PartLabel cubePartLabel;
    TopTools_IndexedMapOfShape subFaces;
    std::unique_ptr<PartSubShapeTool> subShapeTool;
    Handle(XCAFDoc_ShapeTool) shapeTool;
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


TEST_F(PartSubShapeToolTest, SubShapeReturnsValidShape) {
    SubShapeId validId(cubePartLabel, ShapeType::TopAbs_FACE, 1);
    auto shape = subShapeTool->subShape(validId);
    ASSERT_FALSE(shape.IsNull());
    EXPECT_EQ(shape.ShapeType(), ShapeType::TopAbs_FACE);
}

TEST_F(PartSubShapeToolTest, SubShapeIdReturnsValidIdForShape) {
    auto& face = subFaces.FindKey(1);
    auto subId = subShapeTool->subShapeId(face);
    EXPECT_TRUE(subShapeTool->subShapeIdValid(subId));
    EXPECT_EQ(subId.shapeType(), face.ShapeType());
    EXPECT_EQ(subId.subId(), 1);
}


TEST_F(PartSubShapeToolTest, SubShapeIdReturnsValidIdForSubShapeLabel) {
    auto& face = subFaces.FindKey(1);
    auto label = shapeTool->AddSubShape(cubeShapeLabel.label(), face);
    SubShapeLabel subLabel(label);
    auto subId = subShapeTool->subShapeId(subLabel);
    EXPECT_TRUE(subShapeTool->subShapeIdValid(subId));
    EXPECT_EQ(subId.shapeType(), face.ShapeType());
    EXPECT_EQ(subId.subId(), 1);
}

TEST_F(PartSubShapeToolTest, SubShapeLabelReturnsValidForShape) {
    auto& face = subFaces.FindKey(1);
    auto subLabel = subShapeTool->subShapeLabel(face);
    ASSERT_FALSE(subLabel.label().IsNull());
    EXPECT_TRUE(shapeTool->GetShape(subLabel.label()).IsEqual(face));
}

TEST_F(PartSubShapeToolTest, SubShapeLabelReturnsValidForSubShapeId) {
    SubShapeId validId(cubePartLabel, ShapeType::TopAbs_FACE, 1);
    auto& face = subFaces.FindKey(1);
    auto subLabel = subShapeTool->subShapeLabel(validId);
    ASSERT_FALSE(subLabel.label().IsNull());
    EXPECT_TRUE(shapeTool->GetShape(subLabel.label()).IsEqual(face));
}

TEST_F(PartSubShapeToolTest, subShapeLabelsReturnValidSequence) {
    std::vector<int> subIds{1, 3};
    SubShapeIdList ids(cubePartLabel, ShapeType::TopAbs_FACE, subIds);
    auto seq = subShapeTool->subShapeLabels(ids);
   
    ASSERT_EQ(seq.Size(), 2);
    auto face_1 = shapeTool->GetShape(seq(1));
    auto face_3 = shapeTool->GetShape(seq(2));
    ASSERT_FALSE(face_1.IsNull());
    ASSERT_FALSE(face_3.IsNull());
    EXPECT_EQ(face_1.ShapeType(), ShapeType::TopAbs_FACE);
    EXPECT_EQ(face_3.ShapeType(), ShapeType::TopAbs_FACE);
}

TEST_F(PartSubShapeToolTest, subShapeIdsReturnsValidList) {
    auto& face_1 = subFaces.FindKey(1);
    auto& face_3 = subFaces.FindKey(3);
    auto face_1_label = shapeTool->AddSubShape(cubeShapeLabel.label(), face_1);
    auto face_3_label = shapeTool->AddSubShape(cubeShapeLabel.label(), face_3);
    TDF_LabelSequence seq{};
    seq.Append(face_1_label);
    seq.Append(face_3_label);

    auto subIdList = subShapeTool->subShapeIds(seq); 

    ASSERT_EQ(subIdList.subIdVec().size(), 2);
    EXPECT_EQ(subIdList.shapeType(), ShapeType::TopAbs_FACE);
    EXPECT_EQ(subIdList.root(), cubePartLabel);
}


TEST_F(PartSubShapeToolTest, subShapesOfTypeReturnsFullListOfFaces) {
    auto faces = subShapeTool->subShapesOfType(ShapeType::TopAbs_FACE);
    ASSERT_EQ(faces.subIdVec().size(), 6);
}