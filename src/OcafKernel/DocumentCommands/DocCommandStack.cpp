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
        notifyDeltaObservers(delta);
    }
    return commited;
}; 
bool DocCommandStack::undo() {
    auto undone = mDoc->Undo();
    if (undone){
        auto delta = mDoc->GetRedos().First();
        notifyDeltaObservers(delta);
    }
    return undone;
}
bool DocCommandStack::redo() {
    auto redone = mDoc->Undo();
    if (redone){
        auto delta = mDoc->GetUndos().First();
        notifyDeltaObservers(delta);
    }
    return redone;
}

void DocCommandStack::notifyDeltaObservers(Handle(TDF_Delta) aDelta) const {
    for (const auto obs : mObservers){
        obs->processDelta(aDelta);
    }
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

bool DocCommandStack::appendDeltaObserver(AbstractDeltaObserver* aObserver)
{
    if (!aObserver) {
        return false;
    }
    if (!aObserver->setDocument(mDoc)) {
        return false;
    }
    auto [_, inserted] = mObservers.insert(aObserver);
    return inserted;
}

bool DocCommandStack::removeDeltaObserver(AbstractDeltaObserver* aObserver)
{
    if (!aObserver) {
        return false;
    }
    auto erased = mObservers.erase(aObserver);
    return erased > 0;
}

int DocCommandStack::undoSize() const {return mDoc->GetUndos().Size();}
int DocCommandStack::redoSize() const {return mDoc->GetRedos().Size();} 
void DocCommandStack::resetUndos() {mDoc->ClearUndos(); mDoc->ClearRedos();}