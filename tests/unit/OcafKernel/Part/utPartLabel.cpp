#include <gtest/gtest.h>

#include "PartLabel.hpp"
#include "PartPrototypes.hpp"

#include <TDF_Label.hxx>
#include <TDocStd_Document.hxx>
#include <TDocStd_Application.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>

static Handle(TDocStd_Document) makeDoc() {
    Handle(TDocStd_Application) app = new TDocStd_Application();
    Handle(TDocStd_Document) doc;
    app->NewDocument("XmlOcaf", doc);
    return doc;
}


TEST(PartLabelTest, PartLabelThrowsOnLabelNotHavingShape) {
    auto doc = makeDoc();
    auto shapeTool = XCAFDoc_DocumentTool::ShapeTool(doc->Main());
    ASSERT_TRUE(doc);
    ASSERT_TRUE(shapeTool);

    TDF_Label emptyLabel = doc->Main().NewChild();

    EXPECT_THROW({
        PartLabel label(emptyLabel);
    }, LabelDoesNotReferenceShape);
}


TEST(PartLabelTest, toIntVectorReturnsCorrectTagPath) {
    auto doc = makeDoc();
    auto shapeTool = XCAFDoc_DocumentTool::ShapeTool(doc->Main());
    ASSERT_TRUE(doc);
    ASSERT_TRUE(shapeTool);
    auto docLabel = shapeTool->AddShape(PartPrototypes::cube(), false);
    ASSERT_FALSE(docLabel.IsNull());
    
    PartLabel label(docLabel);
    
    std::vector<int> expected = {0, 1, shapeTool->Label().Tag(), docLabel.Tag()};
    EXPECT_EQ(label.toIntVector(), expected);
}

TEST(PartLabelTest, toStringReturnsCorrectTagPath) {
    auto doc = makeDoc();
    auto shapeTool = XCAFDoc_DocumentTool::ShapeTool(doc->Main());
    ASSERT_TRUE(doc);
    ASSERT_TRUE(shapeTool);
    
    auto docLabel = shapeTool->AddShape(PartPrototypes::cube(), false);
    ASSERT_FALSE(docLabel.IsNull());
    
    PartLabel label(docLabel);
   
    auto rootTag = std::to_string(0);
    auto shapeToolTag = std::to_string(shapeTool->Label().Tag());
    auto docLabelTag = std::to_string(docLabel.Tag()); 
    
    std::string expected = rootTag + ":1:" + shapeToolTag + ":" + docLabelTag;    
    EXPECT_EQ(label.toString(), expected);
}