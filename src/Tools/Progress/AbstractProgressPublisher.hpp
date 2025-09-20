#ifndef AbstractProgressPublisher_hpp
#define AbstractProgressPublisher_hpp

#include <string>
#include "ProgressRange.hpp"

class AbstractProgressPublisher {
public:
    virtual ~AbstractProgressPublisher() = default;
    virtual void publishRange(const ProgressRange& aScope) const = 0;
};

class IdleProgressPublisher : public AbstractProgressPublisher {
    void publishRange(const ProgressRange& aScope) const override {};
};

#endif
