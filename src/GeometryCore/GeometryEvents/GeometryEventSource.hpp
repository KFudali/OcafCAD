#ifndef GeometryEventSource_hpp
#define GeometryEventSource_hpp

#include "GeometryObserver.hpp"
#include "MessageSubscriber.hpp"
#include <unordered_set>

#include "PartEvents.hpp"
#include "AssemblyEvents.hpp"

class GeometryEventSource {
    public:
    GeometryEventSource(
        MessageSubscriber& aKernelEvents
    );

    virtual bool appendObserver(GeometryObserver* aObserver);
    virtual bool removeObserver(GeometryObserver* aObserver);
    virtual MessageSubscriber& bus() {return mKernelEvents;};

    private:

    void onPartAddedEvent(const PartAddedEvent&) const;
    void onPartRemovedEvent(const PartRemovedEvent&) const;
    void onPartModifiesEvent() const; // To be implemented
    void onComponentAddedToAssemblyEvent(const ComponentAddedToAssemblyEvent&) const;
    void onComponentRemovedFromAssemblyEvent(const ComponentRemovedFromAssemblyEvent&) const;
    
    MessageSubscriber& mKernelEvents;
    std::unordered_set<GeometryObserver*> mObservers;
    std::vector<std::unique_ptr<AbstractSubscription>> mSubs;
};

#endif