#ifndef DocCommandStack_hpp
#define DocCommandStack_hpp

#include <unordered_set>
#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>
#include <TDF_Delta.hxx>

#include "AbstractDocCommandStack.hpp"
#include "AbstractDeltaObserver.hpp"

class DocCommandStack {
public:
    DocCommandStack(
        Handle(TDocStd_Document) aDocument, 
        size_t aUndoLimit = 30
    );
    
    bool openCommand(); 
    bool commitCommand(); 
    bool abortCommand(); 
    bool undo(); 
    bool redo(); 
    void resetUndos(); 
   
    bool appendDeltaObserver(AbstractDeltaObserver* aObserver); 
    bool removeDeltaObserver(AbstractDeltaObserver* aObserver); 
    
    bool hasOpenCommand() const; 
    int undoSize() const; 
    int redoSize() const; 
private:
    Handle(TDocStd_Document) mDoc;
    DeltaPublisher mDeltaPublisher;
};

#endif