#ifndef AbstractDeltaObserver_hpp
#define AbstractDeltaObserver_hpp

#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>

class AbstractDeltaObserver {
public:
    virtual bool setDocument(Handle(TDocStd_Document) aDocument) = 0;
    virtual bool processDelta(Handle(TDF_Delta) aDelta) const = 0;
};

#endif