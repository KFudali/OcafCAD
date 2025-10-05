#ifndef AbstractDeltaObserver_hpp
#define AbstractDeltaObserver_hpp

#include <Standard_Handle.hxx>

#include <TDF_DeltaOnAddition.hxx>
#include <TDF_DeltaOnRemoval.hxx>
#include <TDF_DeltaOnModification.hxx>
#include <TDF_DeltaOnResume.hxx>
#include <TDF_DeltaOnForget.hxx>

class AbstractDeltaObserver {
    public:
    virtual ~AbstractDeltaObserver() = default;

    virtual void onAddition(Handle(TDF_DeltaOnAddition) aDelta) = 0;
    virtual void onRemoval(Handle(TDF_DeltaOnRemoval) aDelta) = 0;
    virtual void onForget(Handle(TDF_DeltaOnForget) aDelta) = 0;
    virtual void onResume(Handle(TDF_DeltaOnResume) aDelta) = 0;
    virtual void onModification(Handle(TDF_DeltaOnModification) aDelta) = 0;
};


#endif