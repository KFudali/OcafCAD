#ifndef CommandStack_hpp
#define CommandStack_hpp

#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>

class CommandStack {
public:
    CommandStack(
        Handle(TDocStd_Document) aDocument,
        size_t aUndoLimit = 10
    ) : mDoc(aDocument) {
        mDoc->SetUndoLimit(aUndoLimit);
    }

    bool openCommand() { 
        if (hasOpenCommand()) {
            return false;
        } else {
            mDoc->OpenCommand();
            return true;
        }
    };
    bool commitCommand() {return mDoc->CommitCommand();};
    bool abortCommand() {
        if (!hasOpenCommand()) {
            return false;
        } else {
            mDoc->AbortCommand();
            return true;
        }
};

    bool hasOpenCommand() const {return mDoc->HasOpenCommand();}; 

    size_t undoSize() const {return mDoc->GetUndos().Size();}; 
    size_t redoSize() const {return mDoc->GetRedos().Size();};; 

    void resetStack() {mDoc->ClearUndos();}; 

private:
    Handle(TDocStd_Document) mDoc;
};

#endif