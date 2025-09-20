#ifndef EventProgressPublisher_hpp
#define EventProgressPublisher_hpp

#include "AbstractProgressPublisher.hpp"
#include "MessagePublisher.hpp"

class EventProgressPublisher : public AbstractProgressPublisher {
    public:
    EventProgressPublisher(
        std::unique_ptr<MessagePublisher> aMessagePublisher
    ) : mPublisher(std::move(aMessagePublisher)){};

    void publishRange(const ProgressRange& aRange) const override;
    
    private:
    std::unique_ptr<MessagePublisher> mPublisher;
};

#endif