#include "EventProgressPublisher.hpp"
#include "ProgressEvents.hpp"

void EventProgressPublisher::publishRange(const ProgressRange& aRange) const {
    auto message = ProgressMessage(aRange);
    auto event = ProgressRangeEvent(message);
    mPublisher->publish(event);
}