#ifndef AssemblyEvents_hpp
#define AssemblyEvents_hpp

#include "BaseOcafKernelEvent.hpp"
#include "PartLabel.hpp"

class ComponentAddedToAssemblyEvent : public BaseOcafKernelEvent {
public:
    explicit ComponentAddedToAssemblyEvent(PartLabel label) : label(label) {}
    PartLabel label;

    std::string log() const {
        return "ComponentAddedToAssemblyEvent, compLabel: " + label.toString();
    };
};

class ComponentRemovedFromAssemblyEvent : public BaseOcafKernelEvent {
public:
    explicit ComponentRemovedFromAssemblyEvent(PartLabel label) : label(label) {}
    PartLabel label;

    std::string log() const {
        return "ComponentRemovedFromAssemblyEvent, compLabel: " + label.toString();
    };
};

#endif