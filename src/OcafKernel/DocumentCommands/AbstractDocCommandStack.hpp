#ifndef AbstractDocCommandStack_hpp
#define AbstractDocCommandStack_hpp

#include "AbstractDeltaObserver.hpp"

class AbstractDocCommandStack {
public:
    virtual bool openCommand() = 0;
    virtual bool commitCommand() = 0;
    virtual bool abortCommand() = 0;
    virtual bool hasOpenCommand() const = 0;
    virtual bool undo() = 0;
    virtual bool redo() = 0;
    virtual bool appendDeltaObserver(
        AbstractDeltaObserver* aObserver
    ) = 0;

    virtual bool removeDeltaObserver(
        AbstractDeltaObserver* aObserver
    ) = 0;
    virtual int undoSize() const = 0;
    virtual int redoSize() const = 0;
    virtual void resetUndos() = 0;
private:
};

#endif