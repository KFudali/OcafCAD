#include <gtest/gtest.h>

#include "DocLabel.hpp"
#include <TDF_Label.hxx>
#include <TDocStd_Document.hxx>
#include <XCAFApp_Application.hxx>

class DocLabelTest : public ::testing::Test {
protected:
    void SetUp() override {
        app = XCAFApp_Application::GetApplication();
        app->NewDocument("XmlXCAF", doc);
    }

    Handle(XCAFApp_Application) app;
    Handle(TDocStd_Document) doc;
};

TEST_F(DocLabelTest, toIntVectorReturnsCorrectTagPath) {
    auto label = doc->Main().NewChild();
    DocLabel docLabel(label);

    std::vector<int> expected = {0, doc->Main().Tag(), label.Tag()}; 

    EXPECT_EQ(docLabel.toIntVector(), expected);
}

TEST_F(DocLabelTest, toStringReturnsCorrectTagPath) {
    auto label = doc->Main().NewChild();
    DocLabel docLabel(label);
   
    auto mainTagString = std::to_string(doc->Main().Tag());
    auto labelTagString = std::to_string(label.Tag()); 
    std::string expected = "0:" + mainTagString + ":" +  labelTagString;
    EXPECT_EQ(docLabel.toString(), expected);
}