#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "OccProgressIndicator.hpp"
#include "ProgressRange.hpp"

using ::testing::_;

class MockProgressPublisher : public AbstractProgressPublisher {
public:
    MOCK_METHOD(void, publishRange, (const ProgressRange& aRange), (const, override));
};

class OccProgressIndicatorTest : public ::testing::Test {
protected:
    MockProgressPublisher mockPublisher;
    OccProgressIndicator indicator{mockPublisher};
};

TEST_F(OccProgressIndicatorTest, PublishesProgressRangeFromNestedScope) {
    Message_ProgressRange rootRange;
    Message_ProgressScope rootScope(rootRange, "RootTask", 100, false);

    Message_ProgressRange subRange = rootScope.Next(10);
    Message_ProgressScope subScope(subRange, "SubTask", 50, false);

    Message_ProgressRange subSubRange = subScope.Next(20);
    Message_ProgressScope subSubScope(subSubRange, "SubSubTask", 10, false);

    subSubScope.Next(5);

    const ProgressRange* capturedRange = nullptr;
    EXPECT_CALL(mockPublisher, publishRange(_))
        .WillOnce([&](const ProgressRange& aRange) {
            capturedRange = &aRange;
        });

    indicator.Show(subSubScope, false);

    ASSERT_NE(capturedRange, nullptr);

    const ProgressRange* current = capturedRange;
    ASSERT_EQ(current->label(), "RootTask");

    ASSERT_TRUE(current->child().has_value());
    current = &current->child()->get();
    ASSERT_EQ(current->label(), "SubTask");

    ASSERT_TRUE(current->child().has_value());
    current = &current->child()->get();
    ASSERT_EQ(current->label(), "SubSubTask");

    EXPECT_FLOAT_EQ(current->currentProgress().value(), 0.5f); // 5 / 10 = 0.5
}
