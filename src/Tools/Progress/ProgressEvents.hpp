#ifndef ProgressEvents_hpp
#define ProgressEvents_hpp

#include "AbstractEvent.hpp"
#include "ProgressMessage.hpp"
#include <string>
#include <sstream>

class ProgressRangeEvent : public AbstractEvent {
public:
    explicit ProgressRangeEvent(const ProgressMessage& aMessage)
        : progressMessage(aMessage) {}

    std::string log() const override {
        return "ProgressRangeEvent";
    }

    ProgressMessage progressMessage;
};


#endif
