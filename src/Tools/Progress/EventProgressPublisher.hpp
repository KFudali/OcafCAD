#ifndef EventProgressPublisher_hpp
#define EventProgressPublisher_hpp

#include "AbstractProgressPublisher.hpp"
#include "MessagePublisher.hpp"

class EventProgressPublisher : public AbstractProgressPublisher {
    public:
    EventProgressPublisher(
        std::unique_ptr<MessagePublisher> aMessagePublisher
    ) : _publisher(std::move(aMessagePublisher)){};

    void scopeStarted(
        const ProgressScopeId& aScopeId,
        const std::string& aMessage
    ) const override;

    void scopeAdvanced(
        const ProgressScopeId& aScopeId,
        double fraction
    ) const override;

    void scopeFinalized(
        const ProgressScopeId& aScopeId
    ) const override;

    private:
    std::unique_ptr<MessagePublisher> _publisher;
};

#endif