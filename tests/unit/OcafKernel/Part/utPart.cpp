#include <gtest/gtest.h>

#include "PartLabel.hpp"
#include "Part.hpp"

#include "PartPrototypes.hpp"

#include <TDF_Label.hxx>
#include <TDataStd_Name.hxx>
#include <TDocStd_Document.hxx>
#include <TDocStd_Application.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>

static Handle(TDocStd_Document) makeDoc() {
    Handle(TDocStd_Application) app = new TDocStd_Application();
    Handle(TDocStd_Document) doc;
    app->NewDocument("XmlOcaf", doc);
    return doc;
}

class FreePartTest : public ::testing::Test {
    protected:   
    void SetUp() override {
        doc = makeDoc();
        Handle(XCAFDoc_ShapeTool) shapeTool = XCAFDoc_DocumentTool::ShapeTool(
            doc->Main()
        );
        TDF_Label label = shapeTool->AddShape(PartPrototypes::cube(), false);
        Handle(TDataStd_Name) nameAttr;
        if (label.FindAttribute(TDataStd_Name::GetID(), nameAttr)) {
            label.ForgetAttribute(nameAttr);
        }
        partLabel = PartLabel(label);
    }
    PartLabel partLabel;
    Handle(TDocStd_Document) doc;
};

TEST_F(FreePartTest, PartUponCreationHasDefaultNameAndColor) {
    Part part(partLabel);
    EXPECT_EQ(part.color(), Part::defaultPartColor);
    EXPECT_EQ(part.name(), Part::defaultPartName);
}