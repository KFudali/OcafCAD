#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "EventProgressPublisher.hpp"
#include "ProgressEvents.hpp"
#include "SignalMessageBus.hpp"

struct MockSubscriber {
    MOCK_METHOD(int, onProgressScopeStartedEvent, (const ProgressScopeStartedEvent&), ());
    MOCK_METHOD(int, onProgressScopeAdvancedEvent, (const ProgressScopeAdvancedEvent&), ());
    MOCK_METHOD(int, onProgressScopeFinalizedEvent, (const ProgressScopeFinalizedEvent&), ());
};
using StrictMockSubscriber = ::testing::StrictMock<MockSubscriber>;

class EventProgressPublisherTest : public ::testing::Test{
    protected:
    void SetUp(){
        messageBus = std::make_unique<SignalMessageBus>();
        auto messagePublisher = std::make_unique<MessagePublisher>(*messageBus);
        eventProgress = std::make_unique<EventProgressPublisher>(
            std::move(messagePublisher)
        );
        subscriber = std::make_shared<StrictMockSubscriber>();
        messageBus->subscribe<ProgressScopeStartedEvent>(
            subscriber, &MockSubscriber::onProgressScopeStartedEvent
        );
        messageBus->subscribe<ProgressScopeAdvancedEvent>(
            subscriber, &MockSubscriber::onProgressScopeAdvancedEvent
        );
        messageBus->subscribe<ProgressScopeFinalizedEvent>(
            subscriber, &MockSubscriber::onProgressScopeFinalizedEvent
        );
    }
    std::shared_ptr<MockSubscriber> subscriber;
    std::unique_ptr<EventProgressPublisher> eventProgress;
    std::unique_ptr<AbstractMessageBus> messageBus;
};

TEST_F(EventProgressPublisherTest, publishesStartedEventOnScopeStarted) {
    const ProgressScopeId id{std::vector<int>{1,2,3}};
    const std::string message("message");

    EXPECT_CALL(*subscriber, onProgressScopeStartedEvent(testing::AllOf(
        testing::Field(&ProgressScopeStartedEvent::id, testing::Eq(id)),
        testing::Field(&ProgressScopeStartedEvent::message, testing::Eq(message))
    )));

    eventProgress->scopeStarted(id, message);
}

TEST_F(EventProgressPublisherTest, publishesEventOnScopeAdvanced) {
    const ProgressScopeId id{std::vector<int>{1,2,3}};
    const double fraction = 0.5;

    EXPECT_CALL(*subscriber, onProgressScopeAdvancedEvent(testing::AllOf(
        testing::Field(&ProgressScopeAdvancedEvent::id, testing::Eq(id)),
        testing::Field(&ProgressScopeAdvancedEvent::fraction, testing::DoubleEq(fraction))
    )));

    eventProgress->scopeAdvanced(id, fraction);
}

TEST_F(EventProgressPublisherTest, publishesEventOnScopeFinalized) {
    const ProgressScopeId id{std::vector<int>{1,2,3}};

    EXPECT_CALL(*subscriber, onProgressScopeFinalizedEvent(
        testing::Field(&ProgressScopeFinalizedEvent::id, testing::Eq(id))
    ));

    eventProgress->scopeFinalized(id);
}
