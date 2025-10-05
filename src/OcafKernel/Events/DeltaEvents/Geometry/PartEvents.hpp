#ifndef PartEvents_hpp
#define PartEvents_hpp

#include "BaseOcafKernelEvent.hpp"
#include "DocLabel.hpp"
#include "PrototypeLabel.hpp"
#include "PartAttributeType.hpp"

class PartAddedEvent : public BaseOcafKernelEvent {
public:
    explicit PartAddedEvent(DocLabel label) : label(label) {}
    DocLabel label;

    std::string log() const {
        return "PartAddedEvent, label: " + label.toString();
    };
};

class PartRemovedEvent : public BaseOcafKernelEvent {
public:
    explicit PartRemovedEvent(DocLabel label) : label(label) {}
    DocLabel label;

    std::string log() const {
        return "PartRemovedEvent, label: " + label.toString();
    };
};

class PartLocationChangedEvent : public BaseOcafKernelEvent {
public:
    explicit PartLocationChangedEvent(DocLabel label) : label(label) {}
    DocLabel label;

    std::string log() const {
        return "PartLocationChangedEvent, label: " + label.toString();
    };
};

class PartAttributeChanged : public BaseOcafKernelEvent {
    public:
    PartAttributeChanged(DocLabel label, AttributeType attributeEnum)
        : label(label), attributeEnum(attributeEnum) {}

    std::string log() const {
        return "PartAttributeChangedEvent, label: " + label.toString();
    };

    DocLabel label;
    AttributeType attributeEnum;
};

#endif