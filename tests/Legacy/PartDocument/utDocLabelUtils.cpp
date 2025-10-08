#include <gtest/gtest.h>

#include "DocLabelUtils.hpp"

#include <TDF_Label.hxx>
#include <TDocStd_Document.hxx>
#include <XCAFApp_Application.hxx>

#include "StubPartDocument.hpp"
#include "StubPartPrototypes.hpp"
#include "Location.hpp"

class DocLabelUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
        partDoc = std::make_unique<PartDocument>(
            StubPartDocument::partDocument()
        );
    }
    std::unique_ptr<PartDocument> partDoc; 
};

TEST_F(DocLabelUtilsTest, testIsRootAssemblyLabel) {
    auto label = partDoc->rootAssemblyLabel().label();
    EXPECT_TRUE(DocLabelUtils::isRootAssemblyLabel(label));
    ASSERT_FALSE(DocLabelUtils::isPrototypeLabel(label));
    ASSERT_FALSE(DocLabelUtils::isPartLabel(label));
}

TEST_F(DocLabelUtilsTest, testIsPrototypeLabel) {
    auto label = partDoc->addPrototype(StubPartPrototypes::cube()).label();
    EXPECT_FALSE(DocLabelUtils::isRootAssemblyLabel(label));
    ASSERT_TRUE(DocLabelUtils::isPrototypeLabel(label));
    ASSERT_FALSE(DocLabelUtils::isPartLabel(label));
}

TEST_F(DocLabelUtilsTest, testIsPartLabel) {
    auto protoLabel = partDoc->addPrototype(StubPartPrototypes::cube()).label();
    auto label = partDoc->addPart(protoLabel, Location()).label();
    EXPECT_FALSE(DocLabelUtils::isRootAssemblyLabel(label));
    ASSERT_FALSE(DocLabelUtils::isPrototypeLabel(label));
    ASSERT_TRUE(DocLabelUtils::isPartLabel(label));
}