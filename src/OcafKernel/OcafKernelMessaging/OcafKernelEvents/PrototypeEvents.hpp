#ifndef PrototypeEvents_hpp
#define PrototypeEvents_hpp

#include "BaseOcafKernelEvent.hpp"
#include "PrototypeLabel.hpp"

class PrototypeAddedEvent : public BaseOcafKernelEvent {
public:
    explicit PrototypeAddedEvent(PrototypeLabel label) : label(label) {}
    PrototypeLabel label;

    std::string log() const {
        return "PrototypeAddedEvent, label: " + label.toString();
    };
};

class PrototypeRemovedEvent : public BaseOcafKernelEvent {
public:
    explicit PrototypeRemovedEvent(PrototypeLabel label) : label(label) {}
    PrototypeLabel label;
    
    std::string log() const {
        return "PrototypeRemovedEvent, label: " + label.toString();
    };

};

#endif