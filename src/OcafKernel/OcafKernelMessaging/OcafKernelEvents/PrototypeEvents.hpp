#ifndef PrototypeEvents_hpp
#define PrototypeEvents_hpp

#include "BaseOcafKernelEvent.hpp"
#include "PrototypeLabel.hpp"

class PrototypeAddedEvent : public BaseOcafKernelEvent {
public:
    explicit PrototypeAddedEvent(PrototypeLabel label) : label(label) {}
    PrototypeLabel label;
};

class PrototypeRemovedEvent : public BaseOcafKernelEvent {
public:
    explicit PrototypeRemovedEvent(PrototypeLabel label) : label(label) {}
    PrototypeLabel label;
};

#endif