#include <gtest/gtest.h>

#include "RefTreeLabel.hpp"
#include "RefTreeMarkerAttribute.hpp"

#include <XCAFApp_Application.hxx>
#include <TDocStd_Document.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelSequence.hxx>

class RefTreeLabelTest : public ::testing::Test {
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

TEST_F(RefTreeLabelTest, CreateWithReferences) {
    TDF_Label ref1 = doc->Main().NewChild();
    TDF_Label ref2 = doc->Main().NewChild();

    TDF_LabelSequence refs;
    refs.Append(ref1);
    refs.Append(ref2);

    RefTreeLabel refTree(root, refs);

    auto retrievedRefs = refTree.references();
    EXPECT_EQ(retrievedRefs.Length(), 2);
    EXPECT_TRUE(retrievedRefs.Value(1).IsEqual(ref1));
    EXPECT_TRUE(retrievedRefs.Value(2).IsEqual(ref2));
}

TEST_F(RefTreeLabelTest, AppendReferenceAddsNewOne) {
    TDF_Label ref1 = doc->Main().NewChild();

    TDF_LabelSequence refs;
    RefTreeLabel refTree(root, refs);

    bool added = refTree.appendReference(ref1);
    EXPECT_TRUE(added);

    auto retrievedRefs = refTree.references();
    EXPECT_EQ(retrievedRefs.Length(), 1);
    EXPECT_TRUE(retrievedRefs.Value(1).IsEqual(ref1));
}

TEST_F(RefTreeLabelTest, AppendReferenceRejectsDuplicate) {
    TDF_Label ref1 = doc->Main().NewChild();

    TDF_LabelSequence refs;
    refs.Append(ref1);
    RefTreeLabel refTree(root, refs);

    bool added = refTree.appendReference(ref1);
    EXPECT_FALSE(added);

    auto retrievedRefs = refTree.references();
    EXPECT_EQ(retrievedRefs.Length(), 1);
}

TEST_F(RefTreeLabelTest, RemoveReference) {
    TDF_Label ref1 = doc->Main().NewChild();
    TDF_Label ref2 = doc->Main().NewChild();

    TDF_LabelSequence refs;
    refs.Append(ref1);
    refs.Append(ref2);
    RefTreeLabel refTree(root, refs);

    bool removed = refTree.removeReference(ref1);
    EXPECT_TRUE(removed);

    auto retrievedRefs = refTree.references();
    EXPECT_EQ(retrievedRefs.Length(), 1);
    EXPECT_TRUE(retrievedRefs.Value(1).IsEqual(ref2));
}

TEST_F(RefTreeLabelTest, RemoveReferenceReturnsFalseIfMissing) {
    TDF_Label ref1 = doc->Main().NewChild();
    TDF_Label ref2 = doc->Main().NewChild();

    TDF_LabelSequence refs;
    refs.Append(ref1);
    RefTreeLabel refTree(root, refs);

    bool removed = refTree.removeReference(ref2);
    EXPECT_FALSE(removed);

    auto retrievedRefs = refTree.references();
    EXPECT_EQ(retrievedRefs.Length(), 1);
}

TEST_F(RefTreeLabelTest, ThrowsIfConstructedFromInvalidLabel) {
    TDF_Label invalid = doc->Main().NewChild();
    EXPECT_THROW({
        RefTreeLabel invalidTree(invalid);
    }, LabelException);
}
