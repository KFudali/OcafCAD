#include <gtest/gtest.h>
#include "StubOccDocument.hpp"
#include "StubPartPrototypes.hpp"


#include "RootAssembly.hpp"
#include "PrototypeRegistry.hpp"


#include "PartLabel.hpp"
#include "GeometryPart.hpp"
#include "PrototypeLabel.hpp"

class RootAssemblyTest : public ::testing::Test {
protected:
    void SetUp() override {
        rootAssembly = std::make_unique<RootAssembly>(mDoc.doc());
        registry = std::make_unique<PrototypeRegistry>(mDoc.doc());
    }

    std::unique_ptr<RootAssembly> rootAssembly;
    std::unique_ptr<PrototypeRegistry> registry;
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
    PartPrototype cube = StubPartPrototypes::cube();
    auto protoLabel = registry->addPrototype(cube);
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
    PartPrototype cube = StubPartPrototypes::cube();
    auto protoLabel = registry->addPrototype(cube);
    rootAssembly->addPart(protoLabel, Location());

    auto topLevel = rootAssembly->topLevelParts();
    EXPECT_EQ(topLevel.size(), 1);
    EXPECT_TRUE(topLevel[0].isValid());
}

TEST_F(RootAssemblyTest, FreePartsDoNotIncludeNestedAssemblyParts) {
    auto assemblyLabel = rootAssembly->addEmptyAssembly();
    ASSERT_TRUE(assemblyLabel.isValid());
    PartPrototype cube = StubPartPrototypes::cube();
    auto protoLabel = registry->addPrototype(cube);
    
    auto assembly = GeometryPart(assemblyLabel);
    auto compLabel = assembly.addComponent(protoLabel, Location());

    auto free = rootAssembly->freeParts();
    ASSERT_EQ(free.size(), 1);
    EXPECT_EQ(free[0], assemblyLabel);
}

TEST_F(RootAssemblyTest, AddAndClearAssemblyDoesNotCrash) {
    rootAssembly->addEmptyPart();
    rootAssembly->addEmptyAssembly();
    EXPECT_NO_THROW(rootAssembly->clear());
}
