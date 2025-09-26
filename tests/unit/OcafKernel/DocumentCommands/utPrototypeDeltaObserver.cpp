#include <gmock/gmock.h>
#include "OcafKernel.hpp"
#include "PrototypeEvents.hpp"
#include "StubPartPrototypes.hpp"

struct MockProtoEventSubscriber {
    MOCK_METHOD(void, onPrototypeAdded, (const PrototypeAddedEvent&), ());
    MOCK_METHOD(void, onPrototypeRemoved, (const PrototypeRemovedEvent&), ());
};

class PrototypeDeltaObserverTest : public ::testing::Test {
    protected:
    void SetUp() override {
        mKernel = std::make_unique<OcafKernel>(); 
    }
    std::unique_ptr<OcafKernel> mKernel;

};

TEST_F(PrototypeDeltaObserverTest, ObserverPublishesOnNewPrototype) {
    auto subscriber = std::make_shared<MockProtoEventSubscriber>();

    auto sub = mKernel->events().subscribe<PrototypeAddedEvent>(
        subscriber, &MockProtoEventSubscriber::onPrototypeAdded
    );
    EXPECT_CALL(*subscriber, onPrototypeAdded(testing::_)).Times(1);

    mKernel->commands().openCommand();
    mKernel->partDocument().addPrototype(StubPartPrototypes::cube());
    mKernel->commands().commitCommand();
}

TEST_F(PrototypeDeltaObserverTest, ObserverPublishesOnUndoNewPrototype) {
    auto subscriber = std::make_shared<MockProtoEventSubscriber>();

    auto sub = mKernel->events().subscribe<PrototypeRemovedEvent>(
        subscriber, &MockProtoEventSubscriber::onPrototypeRemoved
    );
    mKernel->commands().openCommand();
    mKernel->partDocument().addPrototype(StubPartPrototypes::cube());
    mKernel->commands().commitCommand();

    EXPECT_CALL(*subscriber, onPrototypeRemoved(testing::_)).Times(1);
    mKernel->commands().undo();
}

TEST_F(PrototypeDeltaObserverTest, ObserverPublishesOnRedoNewPrototype) {
    auto subscriber = std::make_shared<MockProtoEventSubscriber>();

    auto sub = mKernel->events().subscribe<PrototypeAddedEvent>(
        subscriber, &MockProtoEventSubscriber::onPrototypeAdded
    );
    mKernel->commands().openCommand();
    mKernel->partDocument().addPrototype(StubPartPrototypes::cube());

    EXPECT_CALL(*subscriber, onPrototypeAdded(testing::_)).Times(1);
    mKernel->commands().commitCommand();
    testing::Mock::VerifyAndClearExpectations(subscriber.get());
    mKernel->commands().undo();
    
    EXPECT_CALL(*subscriber, onPrototypeAdded(testing::_)).Times(1);
    mKernel->commands().redo();
}