#ifndef ProgressEvents_hpp
#define ProgressEvents_hpp

#include "AbstractEvent.hpp"
#include "ProgressMessage.hpp"
#include <string>
#include <sstream>

class ProgressRangeEvent : public AbstractEvent {
public:
    explicit ProgressRangeEvent(const ProgressMessage& aMessage)
        : mProgressMessage(aMessage) {}

    std::string log() const override {
        return "ProgressRangeEvent";
    }
    private:
    ProgressMessage mProgressMessage;
};


#endif
