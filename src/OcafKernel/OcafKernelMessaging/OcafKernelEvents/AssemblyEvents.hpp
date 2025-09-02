#ifndef AssemblyEvents_hpp
#define AssemblyEvents_hpp

#include "BaseOcafKernelEvent.hpp"
#include "PartLabel.hpp"

class ComponentAddedToAssemblyEvent : public BaseOcafKernelEvent {
public:
    explicit ComponentAddedToAssemblyEvent(PartLabel compLabel) : compLabel(compLabel) {}
    PartLabel compLabel;
};

class ComponentRemovedFromAssemblyEvent : public BaseOcafKernelEvent {
public:
    explicit ComponentRemovedFromAssemblyEvent(PartLabel label) : label(label) {}
    PartLabel label;
};

#endif