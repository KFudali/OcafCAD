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
    MockSubscriber mock;

    mMessageBus->subscribe<PrototypeAddedEvent>(
        [&](const PrototypeAddedEvent& e) { mock.onPrototypeAdded(e); });
    mMessageBus->subscribe<PrototypeRemovedEvent>(
        [&](const PrototypeRemovedEvent& e) { mock.onPrototypeRemoved(e); });

    PrototypeLabel label;

    EXPECT_CALL(mock, onPrototypeAdded(
                          testing::Field(&PrototypeAddedEvent::label, label)))
        .Times(1);
    EXPECT_CALL(mock, onPrototypeRemoved(
                          testing::Field(&PrototypeRemovedEvent::label, label)))
        .Times(1);

    mPublisher->publishPrototypeAdded(label);
    mPublisher->publishPrototypeRemoved(label);
}

TEST_F(SignalOcafKernelPublisherTest, PartEventsArePublished) {
    MockSubscriber mock;

    mMessageBus->subscribe<PartAddedEvent>(
        [&](const PartAddedEvent& e) { mock.onPartAdded(e); });
    mMessageBus->subscribe<PartRemovedEvent>(
        [&](const PartRemovedEvent& e) { mock.onPartRemoved(e); });
    mMessageBus->subscribe<PartLocationChangedEvent>(
        [&](const PartLocationChangedEvent& e) {
            mock.onPartLocationChanged(e);
        });
    mMessageBus->subscribe<PartAttributeChanged>(
        [&](const PartAttributeChanged& e) { mock.onPartAttributeChanged(e); });

    PartLabel partLabel;
    PartAttributeType attr = PartAttributeType::Color;

    EXPECT_CALL(mock,
                onPartAdded(testing::Field(&PartAddedEvent::label, partLabel)))
        .Times(1);
    EXPECT_CALL(mock, onPartRemoved(
                          testing::Field(&PartRemovedEvent::label, partLabel)))
        .Times(1);
    EXPECT_CALL(mock, onPartLocationChanged(testing::Field(
                          &PartLocationChangedEvent::label, partLabel)))
        .Times(1);
    EXPECT_CALL(
        mock, onPartAttributeChanged(testing::AllOf(
                  testing::Field(&PartAttributeChanged::label, partLabel),
                  testing::Field(&PartAttributeChanged::attributeEnum, attr))))
        .Times(1);

    mPublisher->publishPartAdded(partLabel);
    mPublisher->publishPartRemoved(partLabel);
    mPublisher->publishPartLocationChanged(partLabel);
    mPublisher->publishPartAttributeChanged(partLabel, attr);
}

TEST_F(SignalOcafKernelPublisherTest, ComponentAssemblyEventsArePublished) {
    MockSubscriber mock;

    mMessageBus->subscribe<ComponentAddedToAssemblyEvent>(
        [&](const ComponentAddedToAssemblyEvent& e) {
            mock.onComponentAddedToAssembly(e);
        });
    mMessageBus->subscribe<ComponentRemovedFromAssemblyEvent>(
        [&](const ComponentRemovedFromAssemblyEvent& e) {
            mock.onComponentRemovedFromAssembly(e);
        });

    PartLabel compLabel;

    EXPECT_CALL(mock, onComponentAddedToAssembly(testing::Field(
                          &ComponentAddedToAssemblyEvent::label, compLabel)))
        .Times(1);
    EXPECT_CALL(mock,
                onComponentRemovedFromAssembly(testing::Field(
                    &ComponentRemovedFromAssemblyEvent::label, compLabel)))
        .Times(1);

    mPublisher->publishComponentAddedToAssembly(compLabel);
    mPublisher->publishComponentRemovedFromAssembly(compLabel);
}
