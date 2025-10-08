#include <gmock/gmock.h>

#include "CommandStack.hpp"
#include "StubPartDocument.hpp"
#include "StubPartPrototypes.hpp"
#include "AbstractDeltaObserver.hpp"

class MockDeltaObserver : public AbstractDeltaObserver {
public:
    MOCK_METHOD(bool, setDocument, (Handle(TDocStd_Document) aDocument), (override));
    MOCK_METHOD(bool, processDelta, (Handle(TDF_Delta) aDelta), (const, override));
};

class CommandStackTest : public ::testing::Test{
    protected:
    void SetUp(){
        mPartDocument = std::make_unique<PartDocument>(StubPartDocument::partDocument());
        mCommands = std::make_unique<CommandStack>(mPartDocument->data());
    }
    std::unique_ptr<PartDocument> mPartDocument;
    std::unique_ptr<AbstractCommandStack> mCommands;
};


TEST_F(CommandStackTest, CommandStackDoesNotAttachObserverWithSetDocument) {
    MockDeltaObserver observer;

    EXPECT_CALL(observer, setDocument(testing::_))
        .WillOnce(testing::Return(false));

    bool appended = mCommands->appendDeltaObserver(&observer);
    EXPECT_FALSE(appended);
}

TEST_F(CommandStackTest, CommandStackCallsProcessDeltaOnAllObserversOnCommit){
    MockDeltaObserver observer;
    EXPECT_CALL(observer, setDocument(testing::_))
        .WillRepeatedly(testing::Return(true));
    bool appended = mCommands->appendDeltaObserver(&observer);
    ASSERT_TRUE(appended);
    mCommands->openCommand();
    mPartDocument->addPrototype(StubPartPrototypes::cube());


    EXPECT_CALL(observer, processDelta(testing::_)).Times(1);
    mCommands->commitCommand();
}


TEST_F(CommandStackTest, CommandStackCallsProcessDeltaOnAllObserversOnUndo){
    MockDeltaObserver observer;
    EXPECT_CALL(observer, setDocument(testing::_))
        .WillRepeatedly(testing::Return(true));
    bool appended = mCommands->appendDeltaObserver(&observer);
    ASSERT_TRUE(appended);
    mCommands->openCommand();
    mPartDocument->addPrototype(StubPartPrototypes::cube());

    EXPECT_CALL(observer, processDelta(testing::_)).Times(1);
    mCommands->commitCommand();

    EXPECT_CALL(observer, processDelta(testing::_)).Times(1);
    mCommands->undo();
}


TEST_F(CommandStackTest, CommandStackCallsProcessDeltaOnAllObserversOnRedo){
    MockDeltaObserver observer;
    EXPECT_CALL(observer, setDocument(testing::_))
        .WillRepeatedly(testing::Return(true));
    bool appended = mCommands->appendDeltaObserver(&observer);
    ASSERT_TRUE(appended);
    mCommands->openCommand();
    mPartDocument->addPrototype(StubPartPrototypes::cube());

    EXPECT_CALL(observer, processDelta(testing::_)).Times(1);
    mCommands->commitCommand();
    
    EXPECT_CALL(observer, processDelta(testing::_)).Times(1);
    mCommands->undo();

    EXPECT_CALL(observer, processDelta(testing::_)).Times(1);
    mCommands->redo();
}

TEST_F(CommandStackTest, MultipleObserversGetNotifiedOnCommit){
    MockDeltaObserver observer_a;
    MockDeltaObserver observer_b;
    EXPECT_CALL(observer_a, setDocument(testing::_))
        .WillRepeatedly(testing::Return(true));
    bool appended_a = mCommands->appendDeltaObserver(&observer_a);
    ASSERT_TRUE(appended_a);

    EXPECT_CALL(observer_b, setDocument(testing::_))
        .WillRepeatedly(testing::Return(true));
    bool appended_b = mCommands->appendDeltaObserver(&observer_b);
    ASSERT_TRUE(appended_b);
    mCommands->openCommand();

    EXPECT_CALL(observer_a, processDelta(testing::_)).Times(1);
    EXPECT_CALL(observer_b, processDelta(testing::_)).Times(1);

    mPartDocument->addPrototype(StubPartPrototypes::cube());
    mCommands->commitCommand();
}

TEST_F(CommandStackTest, RemovedObserverDoesNotgetNotified){
    MockDeltaObserver observer;
    EXPECT_CALL(observer, setDocument(testing::_))
        .WillRepeatedly(testing::Return(true));
    bool appended = mCommands->appendDeltaObserver(&observer);
    ASSERT_TRUE(appended);
    
    bool removed = mCommands->removeDeltaObserver(&observer);
    EXPECT_TRUE(removed);
    
    mCommands->openCommand();
    mPartDocument->addPrototype(StubPartPrototypes::cube());
    mCommands->commitCommand();
}


TEST_F(CommandStackTest, SameObserverCannotBeAddedTwice){
    MockDeltaObserver observer;
    EXPECT_CALL(observer, setDocument(testing::_))
        .WillRepeatedly(testing::Return(true));
    bool appended = mCommands->appendDeltaObserver(&observer);
    ASSERT_TRUE(appended);
    
    bool appended_again = mCommands->appendDeltaObserver(&observer);
    ASSERT_FALSE(appended_again);
}