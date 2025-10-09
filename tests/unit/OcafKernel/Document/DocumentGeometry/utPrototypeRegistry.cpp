#include <gtest/gtest.h>

#include "StubOccDocument.hpp"
#include "StubPartPrototypes.hpp" 

#include "PrototypeRegistry.hpp"
#include "PrototypeLabel.hpp"
#include "PartPrototype.hpp"

class PrototypeRegistryTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_unique<PrototypeRegistry>(mDoc.doc());
    }
    std::unique_ptr<PrototypeRegistry> registry;
    StubOccDocument mDoc;
};

TEST_F(PrototypeRegistryTest, ConstructRegistryInitializesShapeTool) {
    ASSERT_NE(registry, nullptr);
    auto prototypes = registry->prototypeList();
    EXPECT_TRUE(prototypes.empty());
}

TEST_F(PrototypeRegistryTest, AddPrototypeCreatesNewLabel) {
    PartPrototype cube = StubPartPrototypes::cube();

    PrototypeLabel label = registry->addPrototype(cube);
    EXPECT_TRUE(label.isValid());

    auto allPrototypes = registry->prototypeList();
    EXPECT_EQ(allPrototypes.size(), 1);
    EXPECT_TRUE(allPrototypes[0].isValid());
}

TEST_F(PrototypeRegistryTest, AddPrototypeTwiceDoesNotDuplicate) {
    PartPrototype cube = StubPartPrototypes::cube();

    auto first = registry->addPrototype(cube);
    auto second = registry->addPrototype(cube);

    EXPECT_TRUE(first.isValid());
    EXPECT_TRUE(second.isValid());
    EXPECT_TRUE(first.label().IsEqual(second.label()));

    auto allPrototypes = registry->prototypeList();
    EXPECT_EQ(allPrototypes.size(), 1);
}

TEST_F(PrototypeRegistryTest, AddAssemblyPrototypeCreatesNewLabelAlways) {
    PartPrototype cube = StubPartPrototypes::cube();

    auto first = registry->addAssemblyPrototype(cube);
    auto second = registry->addAssemblyPrototype(cube);

    EXPECT_TRUE(first.isValid());
    EXPECT_TRUE(second.isValid());
    EXPECT_FALSE(first.label().IsEqual(second.label()));
}

TEST_F(PrototypeRegistryTest, RemovePrototypeRemovesSuccessfully) {
    PartPrototype cube = StubPartPrototypes::cube();
    auto label = registry->addPrototype(cube);

    ASSERT_TRUE(label.isValid());
    bool removed = registry->removePrototype(label);
    EXPECT_TRUE(removed);

    auto allPrototypes = registry->prototypeList();
    EXPECT_TRUE(allPrototypes.empty());
}

TEST_F(PrototypeRegistryTest, RemovePrototypeWithInvalidLabelFails) {
    PrototypeLabel invalid;
    EXPECT_FALSE(registry->removePrototype(invalid));
}

TEST_F(PrototypeRegistryTest, PrototypeListReflectsAddedPrototypes) {
    PartPrototype cube = StubPartPrototypes::cube();
    PartPrototype sphere = StubPartPrototypes::sphere();

    registry->addPrototype(cube);
    registry->addPrototype(sphere);

    auto allPrototypes = registry->prototypeList();
    EXPECT_EQ(allPrototypes.size(), 2);

    for (const auto& label : allPrototypes)
        EXPECT_TRUE(label.isValid());
}
