#ifndef SignalOcafKernelPublisher_hpp
#define SignalOcafKernelPublisher_hpp

#include "AbstractOcafKernelPublisher.hpp"
#include "AbstractMessageBus.hpp"

#include <memory>
#include <vector>

class SignalOcafKernelPublisher : public AbstractOcafKernelPublisher {

    public:
    SignalOcafKernelPublisher(AbstractMessageBus& aMessageBus);
    
    void publishPrototypeAdded(PrototypeLabel label) override;
    void publishPrototypeRemoved(PrototypeLabel label) override;

    void publishPartAdded(PartLabel label) const override;
    void publishPartRemoved(PartLabel label) const override;
    void publishPartLocationChanged(PartLabel label) const override;
    void publishPartAttributeChanged(
        PartLabel label, PartAttributeType attributeEnum
    ) const override;

    void publishComponentAddedToAssembly(PartLabel compLabel) const override;
    void publishComponentRemovedFromAssembly(PartLabel label) const override;
   
    private:
    AbstractMessageBus& mMessageBus;
};

#endif