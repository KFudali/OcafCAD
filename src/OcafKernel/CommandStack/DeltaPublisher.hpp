#ifndef DeltaPublisher_hpp
#define DeltaPublisher_hpp

#include <Standard_Handle.hxx>
#include <TDF_Delta.hxx>
#include "AbstractDeltaObserver.hpp"
#include <unordered_set>

class DeltaPublisher { 
    public:
    DeltaPublisher() = default;
    virtual ~DeltaPublisher() = default;

    bool processDelta(Handle(TDF_Delta) aDelta) const;
    bool appendDeltaObserver(AbstractDeltaObserver* aDeltaObserver);
    bool removeDeltaObserver(AbstractDeltaObserver* aDeltaObserver);

    private:
    void notifyAddition(Handle(TDF_DeltaOnAddition) aAttrDelta) const;
    void notifyRemoval(Handle(TDF_DeltaOnRemoval) aAttrDelta) const;
    void notifyForget(Handle(TDF_DeltaOnForget) aAttrDelta) const;
    void notifyResume(Handle(TDF_DeltaOnResume) aAttrDelta) const;
    void notifyModification(Handle(TDF_DeltaOnModification) aAttrDelta) const;

    std::unordered_set<AbstractDeltaObserver*> mObservers;
};

#endif