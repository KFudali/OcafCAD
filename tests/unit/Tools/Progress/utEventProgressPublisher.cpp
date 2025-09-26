#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SignalMessageBus.hpp"
#include "EventProgressPublisher.hpp"
#include "ProgressEvents.hpp"
#include "ProgressRange.hpp"

struct MockProgressSubscriber {
    MOCK_METHOD(void, onProgressRangeEvent, (const ProgressRangeEvent&), ());
};

class EventProgressPublisherTest : public ::testing::Test {
protected:
    void SetUp() override {
        messageBus = std::make_shared<SignalMessageBus>();
        publisher = std::make_unique<EventProgressPublisher>(messageBus);
    }
    std::shared_ptr<AbstractMessageBus> messageBus;
    std::unique_ptr<EventProgressPublisher> publisher;
};

TEST_F(EventProgressPublisherTest, PublishesSingleEvent) {
    ProgressRange root("RootTask");
    root.setTo(Fraction(0.1f));
    auto mess = ProgressMessage(root);
    
    auto mockSubscriber = std::make_shared<MockProgressSubscriber>();
    messageBus->subscribe<ProgressRangeEvent>(
        mockSubscriber, &MockProgressSubscriber::onProgressRangeEvent
    );

    EXPECT_CALL(*mockSubscriber, onProgressRangeEvent(::testing::_)).Times(1);
    publisher->publishRange(root);
}

bool verifyProgressRanges(const ProgressRangeEvent& event) {
    const auto& ranges = event.progressMessage.progressRanges;

    if (ranges.size() != 3) return false;
    if (ranges[0].label != "RootTask") return false;
    if (ranges[1].label != "SubTask1") return false;
    if (ranges[2].label != "SubTask2") return false;
    if (ranges[0].progressFraction.value() != 0.1f) return false;
    if (ranges[1].progressFraction.value() != 0.2f) return false;
    if (ranges[2].progressFraction.value() != 0.3f) return false;

    return true;
}

TEST_F(EventProgressPublisherTest, PublishesNestedEvent) {
    ProgressRange root("RootTask");
    auto& sub1 = root.newChild(Fraction(0.0f), "SubTask1");
    auto& sub2 = sub1.newChild(Fraction(0.0f), "SubTask2");

    root.setTo(Fraction(0.1f));
    sub1.setTo(Fraction(0.2f));
    sub2.setTo(Fraction(0.3f));

    auto mockSubscriber = std::make_shared<MockProgressSubscriber>();
    messageBus->subscribe<ProgressRangeEvent>(
        mockSubscriber, &MockProgressSubscriber::onProgressRangeEvent
    );

    EXPECT_CALL(*mockSubscriber, onProgressRangeEvent(
        testing::Truly(verifyProgressRanges))
    ).Times(1);

    publisher->publishRange(root);
}

