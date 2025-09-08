#include <gmock/gmock.h>

#include "DocCommandStack.hpp"
#include "StubPartDocument.hpp"
#include "StubPartPrototypes.hpp"
#include "AbstractDeltaObserver.hpp"

class MockDeltaObserver : public AbstractDeltaObserver {
public:
    MOCK_METHOD(bool, setDocument, (Handle(TDocStd_Document) aDocument), (override));
    MOCK_METHOD(bool, processDelta, (Handle(TDF_Delta) aDelta), (const, override));
};


class DocCommandStackTest : public ::testing::Test{
    protected:
    void SetUp(){
        mPartDocument = std::make_unique<PartDocument>(StubPartDocument::partDocument());
        mCommands = std::make_unique<DocCommandStack>(mPartDocument->data());
    }
    std::unique_ptr<PartDocument> mPartDocument;
    std::unique_ptr<AbstractDocCommandStack> mCommands;
};


TEST_F(DocCommandStackTest, CommandStackDoesNotAttachObserverWithSetDocument) {
    MockDeltaObserver observer;

    EXPECT_CALL(observer, setDocument(testing::_))
        .WillOnce(testing::Return(false));

    bool appended = mCommands->appendDeltaObserver(&observer);
    EXPECT_FALSE(appended);
}

TEST_F(DocCommandStackTest, CommandStackCallsProcessDeltaOnAllObserversOnCommit){
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


TEST_F(DocCommandStackTest, CommandStackCallsProcessDeltaOnAllObserversOnUndo){
    MockDeltaObserver observer;
    EXPECT_CALL(observer, setDocument(testing::_))
        .WillRepeatedly(testing::Return(true));
    bool appended = mCommands->appendDeltaObserver(&observer);
    ASSERT_TRUE(appended);
    mCommands->openCommand();
    mPartDocument->addPrototype(StubPartPrototypes::cube());
    mCommands->commitCommand();

    EXPECT_CALL(observer, processDelta(testing::_)).Times(1);
    mCommands->undo();
}


TEST_F(DocCommandStackTest, CommandStackCallsProcessDeltaOnAllObserversOnRedo){
    MockDeltaObserver observer;
    EXPECT_CALL(observer, setDocument(testing::_))
        .WillRepeatedly(testing::Return(true));
    bool appended = mCommands->appendDeltaObserver(&observer);
    ASSERT_TRUE(appended);
    mCommands->openCommand();
    mPartDocument->addPrototype(StubPartPrototypes::cube());
    mCommands->commitCommand();
    mCommands->undo();

    EXPECT_CALL(observer, processDelta(testing::_)).Times(1);
    mCommands->redo();
}

TEST_F(DocCommandStackTest, MultipleObserversGetNotifiedOnCommit){
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

TEST_F(DocCommandStackTest, RemovedObserverDoesNotgetNotified){
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


TEST_F(DocCommandStackTest, SameObserverCannotBeAddedTwice){
    MockDeltaObserver observer;
    EXPECT_CALL(observer, setDocument(testing::_))
        .WillRepeatedly(testing::Return(true));
    bool appended = mCommands->appendDeltaObserver(&observer);
    ASSERT_TRUE(appended);
    
    bool appended_again = mCommands->appendDeltaObserver(&observer);
    ASSERT_FALSE(appended_again);
}