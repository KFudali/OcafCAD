#ifndef AbstractEvent_hpp
#define AbstractEvent_hpp

#include <string>
#include <concepts>

class AbstractEvent {
public:
    virtual ~AbstractEvent() = default;
    virtual std::string log() const = 0;
};

template<typename EventType>
concept EventConcept = std::derived_from<EventType, AbstractEvent>;

#endif