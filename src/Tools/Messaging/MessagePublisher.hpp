
#ifndef MessagePublisher_hpp
#define MessagePublisher_hpp

#include "AbstractMessageBus.hpp"

class MessagePublisher {
public:
    virtual ~MessagePublisher() = default;
    MessagePublisher(
        AbstractMessageBus& aMessageBus
    ) : mMessageBus(aMessageBus){}
    
    template<EventConcept EventType>
    void publish(const EventType& message) const {
        mMessageBus.publish<EventType>(message);
    }

    private:
    
    AbstractMessageBus& mMessageBus;
};


#endif