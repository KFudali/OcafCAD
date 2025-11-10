#include <gtest/gtest.h>

#include "NamedRefTreeLabel.hpp"
#include "NamedRefTreeAttribute.hpp"

#include <XCAFApp_Application.hxx>
#include <TDocStd_Document.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelSequence.hxx>

class NamedRefLabelTest : public ::testing::Test {
protected:
    void SetUp() override {
        app = XCAFApp_Application::GetApplication();
        app->NewDocument("XmlXCAF", doc);
        root = doc->Main().NewChild();
    }
    Handle(XCAFApp_Application) app;
    Handle(TDocStd_Document) doc;
    TDF_Label root;
};

TEST_F(NamedRefLabelTest, rename) {
    TDF_Label ref1 = doc->Main().NewChild();
    TDF_Label ref2 = doc->Main().NewChild();
    std::string name = "name";
    std::string newName = "newName";

    TDF_LabelSequence refs;
    refs.Append(ref1);
    refs.Append(ref2);

    NamedRefTreeLabel refLabel(root, refs, name);
    EXPECT_EQ(refLabel.name(), name);
    refLabel.rename(newName);
    EXPECT_EQ(refLabel.name(), newName);
}