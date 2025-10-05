#ifndef AssemblyEvents_hpp
#define AssemblyEvents_hpp

#include "BaseOcafKernelEvent.hpp"
#include "DocLabel.hpp"

class ComponentAddedToAssemblyEvent : public BaseOcafKernelEvent {
public:
    explicit ComponentAddedToAssemblyEvent(DocLabel label) : label(label) {}
    DocLabel label;

    std::string log() const {
        return "ComponentAddedToAssemblyEvent, compLabel: " + label.toString();
    };
};

class ComponentRemovedFromAssemblyEvent : public BaseOcafKernelEvent {
public:
    explicit ComponentRemovedFromAssemblyEvent(DocLabel label) : label(label) {}
    DocLabel label;

    std::string log() const {
        return "ComponentRemovedFromAssemblyEvent, compLabel: " + label.toString();
    };
};

#endif