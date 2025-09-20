#include <gtest/gtest.h>
#include <gmock/gmock.h>

// struct MockSubscriber {
//     MOCK_METHOD(int, onProgressScopeStartedEvent, (const ProgressScopeStartedEvent&), ());
//     MOCK_METHOD(int, onProgressScopeAdvancedEvent, (const ProgressScopeAdvancedEvent&), ());
//     MOCK_METHOD(int, onProgressScopeFinalizedEvent, (const ProgressScopeFinalizedEvent&), ());
// };
// using StrictMockSubscriber = ::testing::StrictMock<MockSubscriber>;

// class EventProgressPublisherTest : public ::testing::Test{
//     protected:
//     void SetUp(){
//         messageBus = std::make_unique<SignalMessageBus>();
//         auto messagePublisher = std::make_unique<MessagePublisher>(*messageBus);
//         eventProgress = std::make_unique<EventProgressPublisher>(
//             std::move(messagePublisher)
//         );
//         subscriber = std::make_shared<StrictMockSubscriber>();
//         messageBus->subscribe<ProgressScopeStartedEvent>(
//             subscriber, &MockSubscriber::onProgressScopeStartedEvent
//         );
//         messageBus->subscribe<ProgressScopeAdvancedEvent>(
//             subscriber, &MockSubscriber::onProgressScopeAdvancedEvent
//         );
//         messageBus->subscribe<ProgressScopeFinalizedEvent>(
//             subscriber, &MockSubscriber::onProgressScopeFinalizedEvent
//         );
//     }
//     std::shared_ptr<MockSubscriber> subscriber;
//     std::unique_ptr<EventProgressPublisher> eventProgress;
//     std::unique_ptr<AbstractMessageBus> messageBus;
// };