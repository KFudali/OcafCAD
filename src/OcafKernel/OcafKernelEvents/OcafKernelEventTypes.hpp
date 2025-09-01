#ifndef OcafKernelEventTypes_hpp
#define OcafKernelEventTypes_hpp

enum class OcafKernelEventTypes {
    PrototypeAdded = 0,
    PrototypeRemoved = 1,

    PartAdded = 10,
    PartRemoved = 11,
    PartLocationChanged = 12,
    PartAttributeChanged = 13,

    ComponentAddedToAssembly = 20,
    ComponentRemovedFromAssembly = 21
};

#endif