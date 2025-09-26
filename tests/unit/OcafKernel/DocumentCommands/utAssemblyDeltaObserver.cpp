#include <gmock/gmock.h>
#include "OcafKernel.hpp"
#include "AssemblyEvents.hpp"
#include "StubPartPrototypes.hpp"

struct MockAssemblyEventSubscriber {
    MOCK_METHOD(void, onComponentAddedToAssembly, 
        (const ComponentAddedToAssemblyEvent&), ()
    );
    MOCK_METHOD(void, onComponentRemovedFromAssembly, 
        (const ComponentRemovedFromAssemblyEvent&), ()
    );
};

class AssemblyDeltaObserverTest : public ::testing::Test {
    protected:
    void SetUp() override {
        mKernel = std::make_unique<OcafKernel>(); 
        cubeProtoLabel = mKernel->partDocument().addPrototype(
            StubPartPrototypes::cube()
        );
        auto assemblyLabel = mKernel->partDocument().addEmptyAssembly();
        assembly = std::make_unique<Part>(assemblyLabel);
    }
    std::unique_ptr<OcafKernel> mKernel;
    PrototypeLabel cubeProtoLabel;
    std::unique_ptr<Part> assembly;
};

TEST_F(AssemblyDeltaObserverTest, ObserverPublishesOnComponentAddedToAssembly) {
    auto subscriber = std::make_shared<MockAssemblyEventSubscriber>();

    auto sub = mKernel->events().subscribe<ComponentAddedToAssemblyEvent>(
        subscriber, &MockAssemblyEventSubscriber::onComponentAddedToAssembly
    );
    EXPECT_CALL(*subscriber, onComponentAddedToAssembly(testing::_)).Times(1);

    mKernel->commands().openCommand();
    assembly->addComponent(cubeProtoLabel, Location()); 
    mKernel->commands().commitCommand();
}

TEST_F(AssemblyDeltaObserverTest, ObserverPublishesOnUndoAddingComponent) {
    auto subscriber = std::make_shared<MockAssemblyEventSubscriber>();

    auto sub = mKernel->events().subscribe<ComponentRemovedFromAssemblyEvent>(
        subscriber, &MockAssemblyEventSubscriber::onComponentRemovedFromAssembly
    );
    mKernel->commands().openCommand();
    assembly->addComponent(cubeProtoLabel, Location()); 
    mKernel->commands().commitCommand();

    EXPECT_CALL(*subscriber, onComponentRemovedFromAssembly(testing::_)).Times(1);
    mKernel->commands().undo();
}

TEST_F(AssemblyDeltaObserverTest, ObserverPublishesOnRedoAddingComponent) {
    auto subscriber = std::make_shared<MockAssemblyEventSubscriber>();

    auto sub = mKernel->events().subscribe<ComponentAddedToAssemblyEvent>(
        subscriber, &MockAssemblyEventSubscriber::onComponentAddedToAssembly
    );
    mKernel->commands().openCommand();
    assembly->addComponent(cubeProtoLabel, Location()); 
    
    EXPECT_CALL(*subscriber, onComponentAddedToAssembly(testing::_)).Times(1);
    mKernel->commands().commitCommand();
    testing::Mock::VerifyAndClearExpectations(subscriber.get());
    mKernel->commands().undo();
    
    EXPECT_CALL(*subscriber, onComponentAddedToAssembly(testing::_)).Times(1);
    mKernel->commands().redo();
}
