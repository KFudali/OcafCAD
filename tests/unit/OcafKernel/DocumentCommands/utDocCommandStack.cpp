#include <gmock/gmock.h>

#include "DocCommandStack.hpp"
#include "StubPartDocument.hpp"
#include "AbstractDeltaObserver.hpp"

class MockDeltaObserver : public AbstractDeltaObserver {


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


TEST_F(DocCommandStackTest, CommandStackDoesNotAttachObserverWithSetDocument){

}

TEST_F(DocCommandStackTest, CommandStackCallsProcessDeltaOnAllObserversOnCommit){

}

TEST_F(DocCommandStackTest, CommandStackCallsProcessDeltaOnAllObserversOnUndo){

}


TEST_F(DocCommandStackTest, CommandStackCallsProcessDeltaOnAllObserversOnRedo){

}