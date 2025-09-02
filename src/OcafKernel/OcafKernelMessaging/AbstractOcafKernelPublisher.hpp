#ifndef AbstractOcafKernelPublisher_hpp
#define AbstractOcafKernelPublisher_hpp


#include "OcafKernelConnections.hpp"
#include "PartLabel.hpp"
#include "PrototypeLabel.hpp"
#include "PartAttributeType.hpp"

class AbstractOcafKernelPublisher{
    public:
    virtual ~AbstractOcafKernelPublisher() = default;


    virtual void publishPrototypeAdded(PrototypeLabel aLabel) = 0; 
    virtual void publishPrototypeRemoved(PrototypeLabel aLabel) = 0;
    
    virtual void publishPartAdded(PartLabel aLabel) const = 0;
    virtual void publishPartRemoved(PartLabel aLabel) const = 0;

    virtual void publishPartLocationChanged(
        PartLabel aLabel
    ) const = 0;
    virtual void publishPartAttributeChanged(
        PartLabel aLabel, PartAttributeType aAttribtueEnum
    ) const = 0;

    virtual void publishComponentAddedToAssembly(
        PartLabel aCompLabel
    ) const = 0;
    virtual void publishComponentRemovedFromAssembly(
        PartLabel aLabel
    ) const = 0;
};

#endif