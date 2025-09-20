#ifndef AbstractProgressPublisher_hpp
#define AbstractProgressPublisher_hpp

#include <string>
#include "ProgressRange.hpp"

class AbstractProgressPublisher {
public:
    virtual ~AbstractProgressPublisher() = default;
    virtual void publishScope(const ProgressRange& aScope) const = 0;
};

class IdleProgressPublisher : public AbstractProgressPublisher {
    void publishScope(const ProgressRange& aScope) const override {};
};

#endif
