#ifndef AbstractOcafKernelPublisher_hpp
#define AbstractOcafKernelPublisher_hpp

#include "DocLabel.hpp"
#include "PartAttributeType.hpp"

class AbstractOcafKernelPublisher{
    public:
    virtual ~AbstractOcafKernelPublisher() = default;


    virtual void publishPrototypeAdded(DocLabel aLabel) = 0; 
    virtual void publishPrototypeRemoved(DocLabel aLabel) = 0;
    
    virtual void publishPartAdded(DocLabel aLabel) const = 0;
    virtual void publishPartRemoved(DocLabel aLabel) const = 0;

    virtual void publishPartLocationChanged(
        DocLabel aLabel
    ) const = 0;
    virtual void publishPartAttributeChanged(
        DocLabel aLabel, AttributeType aAttribtueEnum
    ) const = 0;

    virtual void publishComponentAddedToAssembly(
        DocLabel aCompLabel
    ) const = 0;
    virtual void publishComponentRemovedFromAssembly(
        DocLabel aLabel
    ) const = 0;
};

#endif