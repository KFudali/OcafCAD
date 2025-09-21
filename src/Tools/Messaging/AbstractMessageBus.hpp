#ifndef AbstractMessageBus_hpp
#define AbstractMessageBus_hpp

#include "AbstractEvent.hpp"
#include "AbstractSubscription.hpp"

#include <functional>
#include <typeindex>
#include <memory>
#include <any>


class AbstractMessageBus {
public:
    virtual ~AbstractMessageBus() = default;

    template<EventConcept EventType>
    std::unique_ptr<AbstractSubscription> subscribe(
        std::function<void(const EventType&)> handler
    ) {
        return subscribeImpl(
            std::type_index(typeid(EventType)),
            [handler](const std::any& msg) {
                handler(std::any_cast<const EventType&>(msg));
            }
        );
    }
    
    template<EventConcept EventType, typename HandleOwner, typename HandleMethod>
    std::unique_ptr<AbstractSubscription> subscribe(
        std::shared_ptr<HandleOwner> obj,
        HandleMethod memFunc
    ) {
        std::weak_ptr<HandleOwner> weakObj = obj;
        auto handler = [weakObj, memFunc](const EventType& event) {
            if (auto sharedObj = weakObj.lock()) {
                std::invoke(memFunc, sharedObj.get(), event);
            }
        };
        return subscribe<EventType>(handler);
    }

    template<EventConcept EventType>
    void publish(const EventType& message) const {
        publishImpl(std::type_index(typeid(EventType)), std::any(message));
    }

protected:
    virtual std::unique_ptr<AbstractSubscription> subscribeImpl(
        std::type_index type, 
        std::function<void(const std::any&)> handler
    ) = 0;
    virtual void publishImpl(
        std::type_index type, const std::any& message
    ) const = 0;
};

#endif