#ifndef ProgressScopeEvent_hpp
#define ProgressScopeEvent_hpp

#include "AbstractEvent.hpp"
#include "ProgressScopeId.hpp"
#include <string>
#include <sstream>


class ProgressScopeEvent : public AbstractEvent {
public:
    explicit ProgressScopeEvent(const ProgressScopeId& id) : id(id) {}
    virtual ~ProgressScopeEvent() = default;

    virtual std::string log() const = 0;
    const ProgressScopeId id;
};

class ProgressScopeStartedEvent : public ProgressScopeEvent {
public:
    ProgressScopeStartedEvent(
        const ProgressScopeId& id, 
        const std::string& message
    ) : ProgressScopeEvent(id), message(message) {}

    std::string log() const override {
        std::ostringstream oss;
        oss << "ScopeStartedEvent id="  
            << id.toString()
            <<  " message=\"" << message << "\"";
        return oss.str();
    }

    const std::string message;
};

class ProgressScopeAdvancedEvent : public ProgressScopeEvent {
public:
    ProgressScopeAdvancedEvent(
        const ProgressScopeId& id, 
        double fraction
    ) : ProgressScopeEvent(id), fraction(fraction) {}

    std::string log() const override {
        std::ostringstream oss;
        oss << "ScopeAdvancedEvent id="  
            << id.toString()
            <<  " fraction=\"" <<  fraction << "\"";
        return oss.str();
    }

    const double fraction;
};

class ProgressScopeFinalizedEvent : public ProgressScopeEvent {
public:
    explicit ProgressScopeFinalizedEvent(
        const ProgressScopeId& id
    ) : ProgressScopeEvent(id) {}

    std::string log() const override {
        std::ostringstream oss;
        oss << "ScopeFinalizedEvent id="  
            << id.toString();
        return oss.str();
    }
};

#endif
