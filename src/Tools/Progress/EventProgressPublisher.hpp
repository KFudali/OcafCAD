#ifndef EventProgressPublisher_hpp
#define EventProgressPublisher_hpp

#include "AbstractProgressPublisher.hpp"
#include "MessagePublisher.hpp"

class EventProgressPublisher : public AbstractProgressPublisher {
    public:
    EventProgressPublisher(
        std::shared_ptr<AbstractMessageBus> aMessageBus
    ) : mBus(aMessageBus){};

    void publishRange(const ProgressRange& aRange) const override;
    
    private:
    std::shared_ptr<AbstractMessageBus> mBus;
};

#endif