#include "CommandStack.hpp"
#include <TDF_Delta.hxx>

CommandStack::CommandStack(
    Handle(TDocStd_Document) aDocument, 
    size_t aUndoLimit
) : mDoc(aDocument){
    mDoc->SetUndoLimit(aUndoLimit);
}

bool CommandStack::commitCommand() {
    bool commited = mDoc->CommitCommand();
    if (commited){
        auto delta = mDoc->GetUndos().First();
        mDeltaPublisher.processDelta(delta);
    }
    return commited;
}; 
bool CommandStack::undo() {
    auto undone = mDoc->Undo();
    if (undone){
        auto delta = mDoc->GetRedos().First();
        mDeltaPublisher.processDelta(delta);
    }
    return undone;
}
bool CommandStack::redo() {
    auto redos = mDoc->GetAvailableRedos();
    auto redone = mDoc->Redo();
    if (redone){
        auto delta = mDoc->GetUndos().First();
        mDeltaPublisher.processDelta(delta);
    }
    return redone;
}

bool CommandStack::openCommand() {
    if (hasOpenCommand()){
        return false;
    }
    mDoc->OpenCommand();
    return true;
}; 

bool CommandStack::abortCommand() {
    if (hasOpenCommand()){
        mDoc->AbortCommand();
        return true;
    }
    return false;
}; 
bool CommandStack::hasOpenCommand() const { 
    return mDoc->HasOpenCommand();
}; 

bool CommandStack::appendDeltaObserver(AbstractDeltaObserver* aObserver){
    return mDeltaPublisher.appendDeltaObserver(aObserver);
}

bool CommandStack::removeDeltaObserver(AbstractDeltaObserver* aObserver){
    return mDeltaPublisher.removeDeltaObserver(aObserver);
}

int CommandStack::undoSize() const {return mDoc->GetUndos().Size();}
int CommandStack::redoSize() const {return mDoc->GetRedos().Size();} 
void CommandStack::resetUndos() {mDoc->ClearUndos(); mDoc->ClearRedos();}