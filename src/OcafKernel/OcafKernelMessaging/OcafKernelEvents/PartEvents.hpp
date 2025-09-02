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
};

class PartAddedRemoved : public BaseOcafKernelEvent {
public:
    explicit PartAddedRemoved(PartLabel label) : label(label) {}
    PartLabel label;
};

class PartLocationChangedEvent : public BaseOcafKernelEvent {
public:
    explicit PartLocationChangedEvent(PartLabel label) : label(label) {}
    PartLabel label;
};

class PartAttributeChanged : public BaseOcafKernelEvent {
    public:
    PartAttributeChanged(PartLabel label, PartAttributeType attributeEnum)
        : label(label), attributeEnum(attributeEnum) {}
    PartLabel label;
    PartAttributeType attributeEnum;
};

#endif