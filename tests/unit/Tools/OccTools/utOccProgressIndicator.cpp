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
    ::testing::NiceMock<MockProgressPublisher> mockPublisher;
    OccProgressIndicator indicator{mockPublisher};
};

// Helper to validate the ProgressRange structure
static bool isExpectedRange(const ProgressRange& range) {
    const ProgressRange* current = &range;
    if (!current->child().has_value()) return false;
    current = &current->child()->get();
    
    if (current->label() != "RootTask") return false;
    if (!current->child().has_value()) return false;
    current = &current->child()->get();

    if (current->label() != "SubTask") return false;
    if (!current->child().has_value()) return false;
    current = &current->child()->get();

    if (current->label() != "SubSubTask") return false;
    if (std::abs(current->currentProgress().value() - 0.5f) > 1e-6f) return false;

    return true;
}

TEST_F(OccProgressIndicatorTest, PublishesProgressRangeFromNestedScope) {
    Message_ProgressRange rootRange = indicator.Start();
    Message_ProgressScope rootScope(rootRange, "RootTask", 100, false);
    Message_ProgressRange subRange = rootScope.Next(10);
    Message_ProgressScope subScope(subRange, "SubTask", 100, false);
    Message_ProgressRange subSubRange = subScope.Next(20);
    Message_ProgressScope subSubScope(subSubRange, "SubSubTask", 100, false);     
    subSubScope.Next(50);
    using ::testing::Truly;
    using ::testing::AtLeast;
    using ::testing::AnyNumber;

    ON_CALL(mockPublisher, publishRange(_)).WillByDefault([](auto&&){});
    EXPECT_CALL(mockPublisher, publishRange(Truly(isExpectedRange)));
    indicator.Show(subSubScope, false);
    testing::Mock::VerifyAndClearExpectations(&mockPublisher);
}

