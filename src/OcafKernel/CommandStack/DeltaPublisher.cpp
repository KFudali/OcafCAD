#include "DeltaPublisher.hpp"

#include <Standard_Type.hxx>
#include <TDF_AttributeDelta.hxx>
#include <TDF_AttributeDeltaList.hxx>

bool DeltaPublisher::processDelta(Handle(TDF_Delta) aDelta) const {
    if (aDelta.IsNull()) return false;
    TDF_AttributeDeltaList attributeDeltas = aDelta->AttributeDeltas();
    for (auto& attrDelta : attributeDeltas) {
        if (attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnAddition))) {
            notifyAddition(Handle(TDF_DeltaOnAddition)::DownCast(attrDelta));
        } 
        else if (attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnRemoval))) {
            notifyRemoval(Handle(TDF_DeltaOnRemoval)::DownCast(attrDelta));
        } 
        else if (attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnForget))) {
            notifyForget(Handle(TDF_DeltaOnForget)::DownCast(attrDelta));
        }
        else if (attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnResume))) {
            notifyResume(Handle(TDF_DeltaOnResume)::DownCast(attrDelta));
        }
        else if (attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnModification))) {
            notifyModification(Handle(TDF_DeltaOnModification)::DownCast(attrDelta));
        }
    }
    return true;
}
void DeltaPublisher::notifyAddition(
    Handle(TDF_DeltaOnAddition) aAttrDelta
) const { for (const auto obs : mObservers){
        obs->onAddition(aAttrDelta);
    }
}
void DeltaPublisher::notifyRemoval(
    Handle(TDF_DeltaOnRemoval) aAttrDelta
) const {
    for (const auto obs : mObservers){
        obs->onRemoval(aAttrDelta);
    }
}
void DeltaPublisher::notifyForget(
    Handle(TDF_DeltaOnForget) aAttrDelta
) const {
    for (const auto obs : mObservers){
        obs->onForget(aAttrDelta);
    }
}
void DeltaPublisher::notifyResume(
    Handle(TDF_DeltaOnResume) aAttrDelta
) const {
    for (const auto obs : mObservers){
        obs->onResume(aAttrDelta);
    }
}
void DeltaPublisher::notifyModification(
    Handle(TDF_DeltaOnModification) aAttrDelta
) const {
    for (const auto obs : mObservers){
        obs->onModification(aAttrDelta);
    }
}

bool DeltaPublisher::appendDeltaObserver(AbstractDeltaObserver* aObserver){
    if (!aObserver) {
        return false;
    }
    auto [_, inserted] = mObservers.insert(aObserver);
    return inserted;
}

bool DeltaPublisher::removeDeltaObserver(AbstractDeltaObserver* aObserver){
    if (!aObserver) {
        return false;
    }
    auto erased = mObservers.erase(aObserver);
    return erased > 0;
}
