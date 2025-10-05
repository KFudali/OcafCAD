#ifndef CommandStack_hpp
#define CommandStack_hpp

#include <unordered_set>
#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>

#include "DeltaPublisher.hpp"
#include "AbstractDeltaObserver.hpp"

class CommandStack {
public:
    CommandStack(
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