#include <gmock/gmock.h>

#include <memory>

#include "OcafKernelEvents.hpp"
#include "SignalMessageBus.hpp"
#include "SignalOcafKernelPublisher.hpp"

struct MockSubscriber {
    MOCK_METHOD(void, onPrototypeAdded, (const PrototypeAddedEvent&), ());
    MOCK_METHOD(void, onPrototypeRemoved, (const PrototypeRemovedEvent&), ());
    MOCK_METHOD(void, onPartAdded, (const PartAddedEvent&), ());
    MOCK_METHOD(void, onPartRemoved, (const PartRemovedEvent&), ());
    MOCK_METHOD(void, onPartLocationChanged, (const PartLocationChangedEvent&),
                ());
    MOCK_METHOD(void, onPartAttributeChanged, (const PartAttributeChanged&),
                ());
    MOCK_METHOD(void, onComponentAddedToAssembly,
                (const ComponentAddedToAssemblyEvent&), ());
    MOCK_METHOD(void, onComponentRemovedFromAssembly,
                (const ComponentRemovedFromAssemblyEvent&), ());
};

class SignalOcafKernelPublisherTest : public ::testing::Test {
   protected:
    void SetUp() override {
        mMessageBus = std::make_unique<SignalMessageBus>();
        mPublisher = std::make_unique<SignalOcafKernelPublisher>(*mMessageBus);
    }

    std::unique_ptr<AbstractMessageBus> mMessageBus;
    std::unique_ptr<SignalOcafKernelPublisher> mPublisher;
};

TEST_F(SignalOcafKernelPublisherTest, PrototypeEventsArePublished) {
    auto subscriber = std::make_shared<MockSubscriber>();
    auto addedSub = mMessageBus->subscribe<PrototypeAddedEvent>(
        subscriber, &MockSubscriber::onPrototypeAdded
    );
    auto removedSub = mMessageBus->subscribe<PrototypeRemovedEvent>(
        subscriber, &MockSubscriber::onPrototypeRemoved
    );
    PrototypeLabel label;
    EXPECT_CALL(
        *subscriber, 
        onPrototypeAdded(testing::Field(&PrototypeAddedEvent::label, label)))
        .Times(1);
    EXPECT_CALL(
        *subscriber, 
        onPrototypeRemoved(testing::Field(&PrototypeRemovedEvent::label, label)))
        .Times(1);

    mPublisher->publishPrototypeAdded(label);
    mPublisher->publishPrototypeRemoved(label);
}

TEST_F(SignalOcafKernelPublisherTest, PartEventsArePublished) {
    auto subscriber = std::make_shared<MockSubscriber>();
    auto addedSub = mMessageBus->subscribe<PartAddedEvent>(
        subscriber, &MockSubscriber::onPartAdded
    );
    auto removedSub = mMessageBus->subscribe<PartRemovedEvent>(
        subscriber, &MockSubscriber::onPartRemoved
    );
    auto locChangedSub = mMessageBus->subscribe<PartLocationChangedEvent>(
        subscriber, &MockSubscriber::onPartLocationChanged
    );
    auto attrChangedSub = mMessageBus->subscribe<PartAttributeChanged>(
        subscriber, &MockSubscriber::onPartAttributeChanged
    );

    PartLabel partLabel;
    PartAttributeType attr = PartAttributeType::Color;

    EXPECT_CALL(
        *subscriber,
        onPartAdded(testing::Field(&PartAddedEvent::label, partLabel)))
        .Times(1);
    EXPECT_CALL(
        *subscriber, 
        onPartRemoved(testing::Field(&PartRemovedEvent::label, partLabel)))
        .Times(1);
    EXPECT_CALL(
        *subscriber, 
        onPartLocationChanged(testing::Field(&PartLocationChangedEvent::label, partLabel)))
        .Times(1);
    EXPECT_CALL(
        *subscriber, 
        onPartAttributeChanged(
            testing::AllOf(
                testing::Field(&PartAttributeChanged::label, partLabel),
                testing::Field(&PartAttributeChanged::attributeEnum, attr)
            )
        ))
        .Times(1);

    mPublisher->publishPartAdded(partLabel);
    mPublisher->publishPartRemoved(partLabel);
    mPublisher->publishPartLocationChanged(partLabel);
    mPublisher->publishPartAttributeChanged(partLabel, attr);
}

TEST_F(SignalOcafKernelPublisherTest, ComponentAssemblyEventsArePublished) {
    auto subscriber = std::make_shared<MockSubscriber>();
    auto addedSub = mMessageBus->subscribe<ComponentAddedToAssemblyEvent>(
        subscriber, &MockSubscriber::onComponentAddedToAssembly
    );
    auto removedSub = mMessageBus->subscribe<ComponentRemovedFromAssemblyEvent>(
        subscriber, &MockSubscriber::onComponentRemovedFromAssembly
    );

    PartLabel compLabel;
    EXPECT_CALL(
        *subscriber, 
        onComponentAddedToAssembly(
            testing::Field(&ComponentAddedToAssemblyEvent::label, compLabel)
        ))
        .Times(1);
    EXPECT_CALL(
        *subscriber,
        onComponentRemovedFromAssembly(
            testing::Field(&ComponentRemovedFromAssemblyEvent::label, compLabel)
        ))
        .Times(1);

    mPublisher->publishComponentAddedToAssembly(compLabel);
    mPublisher->publishComponentRemovedFromAssembly(compLabel);
}
