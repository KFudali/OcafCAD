#include "GeometryEventSource.hpp"

GeometryEventSource::GeometryEventSource(MessageSubscriber& aKernelEvents)
    : mKernelEvents(aKernelEvents){
    mSubs.push_back(mKernelEvents.subscribe<PartAddedEvent, GeometryEventSource>(
        this, &GeometryEventSource::onPartAddedEvent
    ));

    mSubs.push_back(mKernelEvents.subscribe<PartRemovedEvent, GeometryEventSource>(
        this, &GeometryEventSource::onPartRemovedEvent
    ));

    mSubs.push_back(mKernelEvents.subscribe<ComponentAddedToAssemblyEvent, GeometryEventSource>(
        this, &GeometryEventSource::onComponentAddedToAssemblyEvent
    ));

    mSubs.push_back(mKernelEvents.subscribe<ComponentRemovedFromAssemblyEvent, GeometryEventSource>(
        this, &GeometryEventSource::onComponentRemovedFromAssemblyEvent
    ));

}

bool GeometryEventSource::appendObserver(GeometryObserver* aObserver)
{
    if (!aObserver) {
        return false;
    }
    auto [_, inserted] = mObservers.insert(aObserver);
    return inserted;
}

bool GeometryEventSource::removeObserver(GeometryObserver* aObserver)
{
    if (!aObserver) {
        return false;
    }
    auto erased = mObservers.erase(aObserver);
    return erased > 0;
}

void GeometryEventSource::onPartAddedEvent(const PartAddedEvent& aEvent) const{
    for (const auto obs : mObservers){
        obs->onPartAdded(aEvent.label);
    }
};

void GeometryEventSource::onPartRemovedEvent(const PartRemovedEvent& aEvent) const {
    for (const auto obs : mObservers){
        obs->onPartRemoved(aEvent.label);
    }
}

void GeometryEventSource::onPartModifiesEvent() const {}; // To be implemented

void GeometryEventSource::onComponentAddedToAssemblyEvent(
    const ComponentAddedToAssemblyEvent& aEvent
) const {
    for (const auto obs : mObservers){
        obs->onComponentAddedToAssembly(aEvent.label);
    }
}

void GeometryEventSource::onComponentRemovedFromAssemblyEvent(
    const ComponentRemovedFromAssemblyEvent& aEvent
) const {
    for (const auto obs : mObservers){
        obs->onComponentRemovedFromAssembly(aEvent.label);
    }
}
    