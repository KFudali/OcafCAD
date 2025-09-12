#ifndef EventProgressPublisher_hpp
#define EventProgressPublisher_hpp

#include "AbstractProgressPublisher.hpp"
#include "MessagePublisher.hpp"

class EventProgressPublisher : public AbstractProgressPublisher {
    public:
    EventProgressPublisher(
        std::unique_ptr<MessagePublisher> aMessagePublisher
    ) : mPublisher(std::move(aMessagePublisher)){};

    void scopeLaunched(
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
    std::unique_ptr<MessagePublisher> mPublisher;
};

#endif