
#ifndef MessagePublisher_hpp
#define MessagePublisher_hpp

#include "AbstractMessageBus.hpp"

class MessagePublisher {
public:
    virtual ~MessagePublisher() = default;
    MessagePublisher(
        std::shared_ptr<AbstractMessageBus> aMessageBus
    ) : mMessageBus(aMessageBus){}
    
    template<EventConcept EventType>
    void publish(const EventType& message) const {
        publishImpl(std::type_index(typeid(EventType)), std::any(message));
    }
    private:
    
    std::shared_ptr<AbstractMessageBus> mMessageBus;
};


#endif