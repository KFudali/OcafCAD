#include <gtest/gtest.h>
#include "ProgressMessage.hpp"
#include "ProgressRange.hpp"

TEST(ProgressMessageTest, CreatesSingleRangeView) {
    ProgressRange root("RootTask");
    root.setTo(Fraction(0.5f));

    ProgressMessage msg(root);

    ASSERT_EQ(msg.progressRanges.size(), 1u);
    EXPECT_EQ(msg.progressRanges[0].label, "RootTask");
    EXPECT_EQ(msg.progressRanges[0].progressFraction.value(), 0.5f);
}

TEST(ProgressMessageTest, CreatesChainOfRanges) {
    ProgressRange root("RootTask");
    auto& sub1 = root.newChild("SubTask1", Fraction(0.5f));
    auto& sub2 = sub1.newChild("SubTask2", Fraction(0.5f));

    sub2.setTo(Fraction(0.8f));

    ProgressMessage msg(root);

    ASSERT_EQ(msg.progressRanges.size(), 3u);

    EXPECT_EQ(msg.progressRanges[0].label, "RootTask");
    EXPECT_EQ(msg.progressRanges[1].label, "SubTask1");
    EXPECT_EQ(msg.progressRanges[2].label, "SubTask2");

    EXPECT_EQ(msg.progressRanges[0].progressFraction.value(), 0.2f);
    EXPECT_EQ(msg.progressRanges[1].progressFraction.value(), 0.4f);
    EXPECT_EQ(msg.progressRanges[2].progressFraction.value(), 0.8f);
}

TEST(ProgressMessageTest, HandlesFinalizedRange) {
    ProgressRange root("RootTask");
    root.setTo(Fraction(1.0f));
    root.finalize();

    ProgressMessage msg(root);

    ASSERT_EQ(msg.progressRanges.size(), 1u);
    EXPECT_EQ(msg.progressRanges[0].label, "RootTask");
    EXPECT_EQ(msg.progressRanges[0].progressFraction.value(), 1.0f);
}
