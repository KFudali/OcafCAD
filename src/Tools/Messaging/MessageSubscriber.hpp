#ifndef MessageSubscriber_hpp
#define MessageSubscriber_hpp

#include "AbstractMessageBus.hpp"

class MessageSubscriber {
public:
    virtual ~MessageSubscriber() = default;
    MessageSubscriber(
        AbstractMessageBus& aMessageBus
    ) : mMessageBus(aMessageBus){}

    template<EventConcept EventType>
    std::unique_ptr<AbstractSubscription> subscribe(
        std::function<void(const EventType&)> handler
    ) {
        return mMessageBus.subscribe<EventType>(handler);
    }
    
    template<EventConcept EventType, typename HandleOwner, typename HandleMethod>
    std::unique_ptr<AbstractSubscription> subscribe(
        std::shared_ptr<HandleOwner> obj,
        HandleMethod memFunc
    ) {
        return mMessageBus.subscribe<EventType>(obj, memFunc);
    }
    private:
    AbstractMessageBus& mMessageBus;

};


#endif