#include "EventProgressPublisher.hpp"
#include "ProgressEvents.hpp"

void EventProgressPublisher::scopeStarted(
    const ProgressScopeId& aScopeId,
    const std::string& aMessage
) const {
    _publisher->publish<ProgressScopeStartedEvent>(
        ProgressScopeStartedEvent(aScopeId, aMessage)
    );
};

void EventProgressPublisher::scopeAdvanced(
    const ProgressScopeId& aScopeId,
    double fraction
) const {
    _publisher->publish<ProgressScopeAdvancedEvent>(
        ProgressScopeAdvancedEvent(aScopeId, fraction)
    );
};

void EventProgressPublisher::scopeFinalized(
    const ProgressScopeId& aScopeId
) const {
    _publisher->publish<ProgressScopeFinalizedEvent>(
        ProgressScopeFinalizedEvent(aScopeId)
    );
};

