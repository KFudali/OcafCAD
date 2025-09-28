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

    template<EventConcept EventType, typename HandleOwner>
    std::unique_ptr<AbstractSubscription> subscribe(
        HandleOwner* obj,
        void (HandleOwner::*memFunc)(const EventType&)
    ) {
        auto handler = [obj, memFunc](const EventType& event) {
            std::invoke(memFunc, obj, event);
        };
        return mMessageBus.subscribe<EventType, HandleOwner>(handler);
    }   

    template<EventConcept EventType, typename HandleOwner>
    std::unique_ptr<AbstractSubscription> subscribe(
        const HandleOwner* obj,
        void (HandleOwner::*memFunc)(const EventType&) const
    ) {
        auto handler = [obj, memFunc](const EventType& event) {
            std::invoke(memFunc, obj, event);
        };
        return mMessageBus.subscribe<EventType>(handler);
    }


    private:
    AbstractMessageBus& mMessageBus;

};


#endif