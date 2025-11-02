#include <gtest/gtest.h>

#include "StubOccDocument.hpp"
#include "StubPartPrototypes.hpp" 

#include "ShapeRegistry.hpp"
#include "ShapeLabel.hpp"
#include "Shape.hpp"

class PrototypeRegistryTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_unique<ShapeRegistry>(mDoc.doc());
    }
    std::unique_ptr<ShapeRegistry> registry;
    StubOccDocument mDoc;
};

TEST_F(PrototypeRegistryTest, ConstructRegistryInitializesShapeTool) {
    ASSERT_NE(registry, nullptr);
    auto prototypes = registry->prototypeList();
    EXPECT_TRUE(prototypes.empty());
}

TEST_F(PrototypeRegistryTest, AddPrototypeCreatesNewLabel) {
    Shape cube = StubPartPrototypes::cube();

    ShapeLabel label = registry->addShape(cube);
    EXPECT_TRUE(label.isValid());

    auto allPrototypes = registry->prototypeList();
    EXPECT_EQ(allPrototypes.size(), 1);
    EXPECT_TRUE(allPrototypes[0].isValid());
}

TEST_F(PrototypeRegistryTest, AddPrototypeTwiceDoesNotDuplicate) {
    Shape cube = StubPartPrototypes::cube();

    auto first = registry->addShape(cube);
    auto second = registry->addShape(cube);

    EXPECT_TRUE(first.isValid());
    EXPECT_TRUE(second.isValid());
    EXPECT_TRUE(first.label().IsEqual(second.label()));

    auto allPrototypes = registry->prototypeList();
    EXPECT_EQ(allPrototypes.size(), 1);
}

TEST_F(PrototypeRegistryTest, AddAssemblyPrototypeCreatesNewLabelAlways) {
    Shape cube = StubPartPrototypes::cube();

    auto first = registry->addAssemblyPrototype(cube);
    auto second = registry->addAssemblyPrototype(cube);

    EXPECT_TRUE(first.isValid());
    EXPECT_TRUE(second.isValid());
    EXPECT_FALSE(first.label().IsEqual(second.label()));
}

TEST_F(PrototypeRegistryTest, RemovePrototypeRemovesSuccessfully) {
    Shape cube = StubPartPrototypes::cube();
    auto label = registry->addShape(cube);

    ASSERT_TRUE(label.isValid());
    bool removed = registry->removePrototype(label);
    EXPECT_TRUE(removed);

    auto allPrototypes = registry->prototypeList();
    EXPECT_TRUE(allPrototypes.empty());
}

TEST_F(PrototypeRegistryTest, RemovePrototypeWithInvalidLabelFails) {
    ShapeLabel invalid;
    EXPECT_FALSE(registry->removePrototype(invalid));
}

TEST_F(PrototypeRegistryTest, PrototypeListReflectsAddedPrototypes) {
    Shape cube = StubPartPrototypes::cube();
    Shape sphere = StubPartPrototypes::sphere();

    registry->addShape(cube);
    registry->addShape(sphere);

    auto allPrototypes = registry->prototypeList();
    EXPECT_EQ(allPrototypes.size(), 2);

    for (const auto& label : allPrototypes)
        EXPECT_TRUE(label.isValid());
}
