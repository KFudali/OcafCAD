#ifndef PrototypeEvents_hpp
#define PrototypeEvents_hpp

#include "BaseOcafKernelEvent.hpp"
#include "DocLabel.hpp"

class PrototypeAddedEvent : public BaseOcafKernelEvent {
public:
    explicit PrototypeAddedEvent(DocLabel label) : label(label) {}
    DocLabel label;

    std::string log() const {
        return "PrototypeAddedEvent, label: " + label.toString();
    };
};

class PrototypeRemovedEvent : public BaseOcafKernelEvent {
public:
    explicit PrototypeRemovedEvent(DocLabel label) : label(label) {}
    DocLabel label;
    
    std::string log() const {
        return "PrototypeRemovedEvent, label: " + label.toString();
    };

};

#endif