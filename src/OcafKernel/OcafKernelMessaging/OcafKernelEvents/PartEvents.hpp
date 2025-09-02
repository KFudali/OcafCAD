#ifndef PartEvents_hpp
#define PartEvents_hpp

#include "BaseOcafKernelEvent.hpp"
#include "PartLabel.hpp"
#include "PrototypeLabel.hpp"
#include "PartAttributeType.hpp"

class PartAddedEvent : public BaseOcafKernelEvent {
public:
    explicit PartAddedEvent(PartLabel label) : label(label) {}
    PartLabel label;

    std::string log() const {
        return "PartAddedEvent, label: " + label.toString();
    };
};

class PartRemovedEvent : public BaseOcafKernelEvent {
public:
    explicit PartRemovedEvent(PartLabel label) : label(label) {}
    PartLabel label;

    std::string log() const {
        return "PartRemovedEvent, label: " + label.toString();
    };
};

class PartLocationChangedEvent : public BaseOcafKernelEvent {
public:
    explicit PartLocationChangedEvent(PartLabel label) : label(label) {}
    PartLabel label;

    std::string log() const {
        return "PartLocationChangedEvent, label: " + label.toString();
    };
};

class PartAttributeChanged : public BaseOcafKernelEvent {
    public:
    PartAttributeChanged(PartLabel label, PartAttributeType attributeEnum)
        : label(label), attributeEnum(attributeEnum) {}

    std::string log() const {
        return "PartAttributeChangedEvent, label: " + label.toString();
    };

    PartLabel label;
    PartAttributeType attributeEnum;
};

#endif