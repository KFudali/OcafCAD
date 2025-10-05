#include "DocCommandStack.hpp"

DocCommandStack::DocCommandStack(
    Handle(TDocStd_Document) aDocument, 
    size_t aUndoLimit
) : mDoc(aDocument){
    mDoc->SetUndoLimit(aUndoLimit);
}

bool DocCommandStack::commitCommand() {
    bool commited = mDoc->CommitCommand();
    if (commited){
        auto delta = mDoc->GetUndos().First();
        mDeltaPublisher.processDelta(delta);
    }
    return commited;
}; 
bool DocCommandStack::undo() {
    auto undone = mDoc->Undo();
    if (undone){
        auto delta = mDoc->GetRedos().First();
        mDeltaPublisher.processDelta(delta);
    }
    return undone;
}
bool DocCommandStack::redo() {
    auto redos = mDoc->GetAvailableRedos();
    auto redone = mDoc->Redo();
    if (redone){
        auto delta = mDoc->GetUndos().First();
        mDeltaPublisher.processDelta(delta);
    }
    return redone;
}

bool DocCommandStack::openCommand() {
    if (hasOpenCommand()){
        return false;
    }
    mDoc->OpenCommand();
    return true;
}; 

bool DocCommandStack::abortCommand() {
    if (hasOpenCommand()){
        mDoc->AbortCommand();
        return true;
    }
    return false;
}; 
bool DocCommandStack::hasOpenCommand() const { 
    return mDoc->HasOpenCommand();
}; 

bool DocCommandStack::appendDeltaObserver(AbstractDeltaObserver* aObserver){
    return mDeltaPublisher.appendDeltaObserver(aObserver);
}

bool DocCommandStack::removeDeltaObserver(AbstractDeltaObserver* aObserver){
    return mDeltaPublisher.removeDeltaObserver(aObserver);
}

int DocCommandStack::undoSize() const {return mDoc->GetUndos().Size();}
int DocCommandStack::redoSize() const {return mDoc->GetRedos().Size();} 
void DocCommandStack::resetUndos() {mDoc->ClearUndos(); mDoc->ClearRedos();}