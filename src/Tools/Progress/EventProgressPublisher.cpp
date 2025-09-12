#include "EventProgressPublisher.hpp"
#include "ProgressEvents.hpp"

void EventProgressPublisher::scopeLaunched(
    const ProgressScopeId& aScopeId,
    const std::string& aMessage
) const {
    mPublisher->publish<ProgressScopeStartedEvent>(
        ProgressScopeStartedEvent(aScopeId, aMessage)
    );
};

void EventProgressPublisher::scopeAdvanced(
    const ProgressScopeId& aScopeId,
    double fraction
) const {
    mPublisher->publish<ProgressScopeAdvancedEvent>(
        ProgressScopeAdvancedEvent(aScopeId, fraction)
    );
};

void EventProgressPublisher::scopeFinalized(
    const ProgressScopeId& aScopeId
) const {
    mPublisher->publish<ProgressScopeFinalizedEvent>(
        ProgressScopeFinalizedEvent(aScopeId)
    );
};

