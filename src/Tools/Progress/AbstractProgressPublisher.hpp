#ifndef AbstractProgressPublisher_hpp
#define AbstractProgressPublisher_hpp

#include <string>
#include "ProgressScopeId.hpp"

class AbstractProgressPublisher {
public:
    virtual ~AbstractProgressPublisher() = default;

    virtual void scopeStarted(
        const ProgressScopeId& aScopeId,
        const std::string& aMessage
    ) const = 0;

    virtual void scopeAdvanced(
        const ProgressScopeId& aScopeId,
        double fraction
    ) const = 0;

    virtual void scopeFinalized(
        const ProgressScopeId& aScopeId
    ) const = 0;
};

#endif
