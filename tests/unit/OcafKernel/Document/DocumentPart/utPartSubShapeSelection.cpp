#include <gtest/gtest.h>

#include "DocumentGeometryFixture.hpp"
#include "PartSubShapeSelection.hpp"

#include <XCAFApp_Application.hxx>
#include <TDocStd_Document.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelSequence.hxx>
#include <TopExp.hxx>
#include <unordered_set>

#include <gtest/gtest.h>
#include "PartSubShapeSelection.hpp"

class PartSubShapeSelectionTest : public DocumentGeometryFixture {
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


TEST_F(PartSubShapeSelectionTest, idsReturnsValidSubShapeList) {
    auto anyParent = cubeShapeLabel.label().NewChild();
    PartSubShapeSelection selection(cubePartLabel, anyParent, faceSeq);
    auto subShapeIds = selection.ids();

    ASSERT_EQ(subShapeIds.subIds().size(), 2);
    auto seq = subShapeTool->subShapeLabels(subShapeIds);

    std::unordered_set<TDF_Label> seqSet;
    std::unordered_set<TDF_Label> faceSeqSet;

    for (Standard_Integer i = 1; i <= seq.Size(); ++i)
        seqSet.insert(seq.Value(i));

    for (Standard_Integer i = 1; i <= faceSeq.Size(); ++i)
        faceSeqSet.insert(faceSeq.Value(i));

    EXPECT_EQ(seqSet, faceSeqSet);
}

TEST_F(PartSubShapeSelectionTest, removeRemovesLabelFromSelection) {
    auto anyParent = cubeShapeLabel.label().NewChild();
    PartSubShapeSelection selection(cubePartLabel, anyParent, faceSeq);
    
    auto subShapeIds = selection.ids();
    ASSERT_EQ(subShapeIds.subIds().size(), 2);
    
    selection.remove(subShapeIds.subIds()[0]);

    auto newSubShapeIds = selection.ids();
    ASSERT_EQ(newSubShapeIds.subIds().size(), 1);
    EXPECT_EQ(newSubShapeIds.subIds()[0], subShapeIds.subIds()[1]);
}

TEST_F(PartSubShapeSelectionTest, appendCanAddNewSubShapeIdToSelection) {
    auto anyParent = cubeShapeLabel.label().NewChild();
    PartSubShapeSelection selection(cubePartLabel, anyParent, faceSeq);
    
    auto subShapeIds = selection.ids();
    ASSERT_EQ(subShapeIds.subIds().size(), 2);

    SubShapeId newId(cubePartLabel, ShapeType::TopAbs_FACE, 3);
    selection.append(newId);

    subShapeIds = selection.ids();
    ASSERT_EQ(subShapeIds.subIds().size(), 3);
}

TEST_F(PartSubShapeSelectionTest, SelectionCanBeReconstructedFromLabel) {
    RefTreeLabel* refLabel;
    {
        auto anyParent = cubeShapeLabel.label().NewChild();
        PartSubShapeSelection selection(cubePartLabel, anyParent, faceSeq);
        refLabel = selection.label();
    }
    PartSubShapeSelection selection{cubePartLabel, *refLabel};
    auto subShapeIds = selection.ids();
    ASSERT_EQ(subShapeIds.subIds().size(), 2);
}