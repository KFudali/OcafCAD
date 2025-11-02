#include <gtest/gtest.h>
#include "StubOccDocument.hpp"
#include "StubPartPrototypes.hpp"

#include "RootAssembly.hpp"
#include "ShapeRegistry.hpp"

#include "PartLabel.hpp"
#include "Part.hpp"
#include "ShapeLabel.hpp"

class RootAssemblyTest : public ::testing::Test {
protected:
    void SetUp() override {
        rootAssembly = std::make_unique<RootAssembly>(mDoc.doc());
        registry = std::make_unique<ShapeRegistry>(mDoc.doc());
    }

    std::unique_ptr<RootAssembly> rootAssembly;
    std::unique_ptr<ShapeRegistry> registry;
    StubOccDocument mDoc;
};

TEST_F(RootAssemblyTest, ConstructedAssemblyIsMarkedAsRoot) {
    TDF_Label label = rootAssembly->label().label();
    EXPECT_TRUE(RootAssembly::isRootAssembly(label));
}

TEST_F(RootAssemblyTest, AddEmptyPartCreatesAValidPartLabel) {
    PartLabel partLabel = rootAssembly->addEmptyPart();
    EXPECT_TRUE(partLabel.isValid());
    EXPECT_FALSE(rootAssembly->freeParts().empty());
}

TEST_F(RootAssemblyTest, AddEmptyAssemblyCreatesAssemblyLabel) {
    PartLabel assemblyLabel = rootAssembly->addEmptyAssembly();
    EXPECT_TRUE(assemblyLabel.isValid());
}

TEST_F(RootAssemblyTest, AddPartFromPrototypeCreatesComponentUnderRoot) {
    Shape cube = StubPartPrototypes::cube();
    auto protoLabel = registry->addShape(cube);
    ASSERT_TRUE(protoLabel.isValid());

    PartLabel part = rootAssembly->addPart(protoLabel, Location());
    EXPECT_TRUE(part.isValid());

    auto topParts = rootAssembly->topLevelParts();
    EXPECT_EQ(topParts.size(), 1);
    EXPECT_TRUE(topParts[0].isValid());
}

TEST_F(RootAssemblyTest, FreePartsIncludeAddedEmptyPart) {
    rootAssembly->addEmptyPart();
    auto free = rootAssembly->freeParts();
    EXPECT_EQ(free.size(), 1);
    EXPECT_TRUE(free[0].isValid());
}

TEST_F(RootAssemblyTest, TopLevelPartsIncludePrototypeParts) {
    Shape cube = StubPartPrototypes::cube();
    auto protoLabel = registry->addShape(cube);
    rootAssembly->addPart(protoLabel, Location());

    auto topLevel = rootAssembly->topLevelParts();
    EXPECT_EQ(topLevel.size(), 1);
    EXPECT_TRUE(topLevel[0].isValid());
}

TEST_F(RootAssemblyTest, FreePartsDoNotIncludeNestedAssemblyParts) {
    auto assemblyLabel = rootAssembly->addEmptyAssembly();
    ASSERT_TRUE(assemblyLabel.isValid());
    Shape cube = StubPartPrototypes::cube();
    auto protoLabel = registry->addShape(cube);
    
    auto assembly = Part(assemblyLabel);
    auto compLabel = assembly.assembly().addComponent(protoLabel, Location());

    auto free = rootAssembly->freeParts();
    ASSERT_EQ(free.size(), 1);
    EXPECT_EQ(free[0], assemblyLabel);
}

TEST_F(RootAssemblyTest, AddAndClearAssemblyDoesNotCrash) {
    rootAssembly->addEmptyPart();
    rootAssembly->addEmptyAssembly();
    EXPECT_NO_THROW(rootAssembly->clear());
}
