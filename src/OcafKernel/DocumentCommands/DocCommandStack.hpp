#ifndef DocCommandStack_hpp
#define DocCommandStack_hpp

#include <unordered_set>
#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>
#include <TDF_Delta.hxx>

#include "AbstractDocCommandStack.hpp"
#include "AbstractDeltaObserver.hpp"

class DocCommandStack : public AbstractDocCommandStack {
public:
    DocCommandStack(
        Handle(TDocStd_Document) aDocument, 
        size_t aUndoLimit = 30
    );
    
    bool openCommand() override; 
    bool commitCommand() override; 
    bool abortCommand() override; 
    bool hasOpenCommand() const override; 
    bool undo() override; 
    bool redo() override; 
    bool appendDeltaObserver(AbstractDeltaObserver* aObserver) override; 
    bool removeDeltaObserver(AbstractDeltaObserver* aObserver) override; 
    int undoSize() const override; 
    int redoSize() const override; 
    void resetUndos() override; 

private:
    void notifyDeltaObservers(Handle(TDF_Delta) aDelta) const;

    Handle(TDocStd_Document) mDoc;
    std::unordered_set<AbstractDeltaObserver*> mObservers;
};

#endif