#ifndef ProgressScopeEvent_hpp
#define ProgressScopeEvent_hpp

#include "AbstractEvent.hpp"
#include <string>
#include <sstream>


class ProgressScopeEvent : public AbstractEvent {
public:
    explicit ProgressScopeEvent(){}
    virtual ~ProgressScopeEvent() = default;

    virtual std::string log() const = 0;
};

#endif
