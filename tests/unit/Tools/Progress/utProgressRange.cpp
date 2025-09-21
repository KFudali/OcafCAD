#include <gtest/gtest.h>
#include "ProgressRange.hpp"

TEST(ProgressRangeTest, ConstructionAndLabel) {
    ProgressRange root("Root");
    EXPECT_TRUE(root.currentProgress().isZero());
    EXPECT_EQ(root.label(), "Root");
    EXPECT_FALSE(root.finalized());
    EXPECT_FALSE(root.parent());
    EXPECT_EQ(root.child(), std::nullopt);
}

TEST(ProgressRangeTest, AdvanceTo) {
    ProgressRange root("Root");

    root.advanceBy(Fraction(0.3f));
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.3f);
    EXPECT_FALSE(root.finalized());

    root.advanceBy(Fraction(0.4f));
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.7f);
    EXPECT_FALSE(root.finalized());
    
    root.advanceBy(Fraction(0.4f));
    EXPECT_TRUE(root.currentProgress().isOne());
    EXPECT_TRUE(root.finalized());
}

TEST(ProgressRangeTest, SetTo) {
    ProgressRange root("Root");

    root.setTo(Fraction(0.3f));
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.3f);
    EXPECT_FALSE(root.finalized());

    root.setTo(Fraction(0.4f));
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.4f);
    EXPECT_FALSE(root.finalized());
    
    root.setTo(Fraction(0.1f));
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.1f);
    EXPECT_FALSE(root.finalized());

    root.setTo(Fraction(2.0f));
    EXPECT_TRUE(root.currentProgress().isOne());
    EXPECT_TRUE(root.finalized());
}


TEST(ProgressRangeTest, FinalizeBehavior) {
    ProgressRange root("Root");
    root.advanceBy(Fraction(0.5f));
    root.finalize();

    EXPECT_TRUE(root.finalized());
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.5f);
}

TEST(ProgressRangeTest, ResetBehavior) {
    ProgressRange root("Root");

    root.advanceBy(Fraction(0.5f));

    root.reset();
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.0f);
    EXPECT_FALSE(root.finalized());

    root.finalize();
    root.reset();
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.0f);
    EXPECT_FALSE(root.finalized());
}

TEST(ProgressRangeTest, SubrangeCreationAndWeight) {
    ProgressRange root("Root");

    auto& child1 = root.newChild("Child1", Fraction(0.6f));
    EXPECT_FLOAT_EQ(root.remainingWeight().value(), 0.4f);
    EXPECT_FLOAT_EQ(child1.currentProgress().value(), 0.0f);
    EXPECT_FLOAT_EQ(child1.weightInParent().value(), 0.6f);
    root.finalizeAndClearChild();

    auto& child2 = root.newChild("Child2");
    EXPECT_FLOAT_EQ(root.remainingWeight().value(), 0.0f);
    EXPECT_FLOAT_EQ(child2.weightInParent().value(), 0.4f);
}

TEST(ProgressRangeTest, ParentProgressPropagation) {
    ProgressRange root("Root");
    auto& child = root.newChild("Child", Fraction(0.5f));

    child.advanceBy(Fraction(0.5f));
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.25f);

    child.finalize();
    EXPECT_TRUE(child.finalized());
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.5f);
}

TEST(ProgressRangeTest, ParentProgressRetractOnSetToAndReset) {
    ProgressRange root("Root");
    auto& child = root.newChild("Child");

    child.advanceBy(Fraction(0.5f));
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.5f);

    child.setTo(Fraction(0.2f));
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.2f);

    child.reset();
    EXPECT_FLOAT_EQ(root.currentProgress().value(), 0.0f);
}

TEST(ProgressRangeTest, NewChildThrowsIfChildAlreadyExists) {
    ProgressRange root("Root");

    auto& child1 = root.newChild("Child1", Fraction(0.5f));
    EXPECT_EQ(child1.label(), "Child1");

    EXPECT_THROW({
        root.newChild("Child2", Fraction(0.5f));
    }, std::logic_error);
}

TEST(ProgressRangeTest, ClearChildFinalizesAndRemovesChild) {
    ProgressRange root("Root");

    auto& child = root.newChild("Child", Fraction(0.0f));
    EXPECT_TRUE(root.child().has_value());
    EXPECT_FALSE(child.finalized());

    root.finalizeAndClearChild();

    EXPECT_FALSE(root.child().has_value());
    EXPECT_FALSE(root.finalized());
}
