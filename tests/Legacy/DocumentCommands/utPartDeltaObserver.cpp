#include <gmock/gmock.h>
#include "OcafKernel.hpp"
#include "PartEvents.hpp"
#include "StubPartPrototypes.hpp"

struct  MockPartEventSubscriber {
    MOCK_METHOD(void, onPartAdded, (const PartAddedEvent&), ());
    MOCK_METHOD(void, onPartRemoved, (const PartRemovedEvent&), ());
};

class PartDeltaObserverTest : public ::testing::Test {
    protected:
    void SetUp() override {
        mKernel = std::make_unique<OcafKernel>(); 
        cubeProtoLabel = mKernel->partDocument().addPrototype(
            StubPartPrototypes::cube()
        );
    }
    std::unique_ptr<OcafKernel> mKernel;
    PrototypeLabel cubeProtoLabel;
};

TEST_F(PartDeltaObserverTest, ObserverPublishesOnNewPart) {
    auto subscriber = std::make_shared< MockPartEventSubscriber>();
    auto sub = mKernel->events().subscribe<PartAddedEvent>(
        subscriber, & MockPartEventSubscriber::onPartAdded
    );
    EXPECT_CALL(*subscriber, onPartAdded(testing::_)).Times(1);

    mKernel->commands().openCommand();
    mKernel->partDocument().addPart(cubeProtoLabel, Location());
    mKernel->commands().commitCommand();
}

TEST_F(PartDeltaObserverTest, ObserverPublishesOnUndoNewPart) {
    auto subscriber = std::make_shared< MockPartEventSubscriber>();

    auto sub = mKernel->events().subscribe<PartRemovedEvent>(
        subscriber, & MockPartEventSubscriber::onPartRemoved
    );
    mKernel->commands().openCommand();
    mKernel->partDocument().addPart(cubeProtoLabel, Location());
    mKernel->commands().commitCommand();

    EXPECT_CALL(*subscriber, onPartRemoved(testing::_)).Times(1);
    mKernel->commands().undo();
}

TEST_F(PartDeltaObserverTest, ObserverPublishesOnRedoNewPart) {
    auto subscriber = std::make_shared< MockPartEventSubscriber>();

    auto sub = mKernel->events().subscribe<PartAddedEvent>(
        subscriber, & MockPartEventSubscriber::onPartAdded
    );
    mKernel->commands().openCommand();
    mKernel->partDocument().addPart(cubeProtoLabel, Location());

    EXPECT_CALL(*subscriber, onPartAdded(testing::_)).Times(1);
    mKernel->commands().commitCommand();
    testing::Mock::VerifyAndClearExpectations(subscriber.get());
    mKernel->commands().undo();
    
    EXPECT_CALL(*subscriber, onPartAdded(testing::_)).Times(1);
    mKernel->commands().redo();
}