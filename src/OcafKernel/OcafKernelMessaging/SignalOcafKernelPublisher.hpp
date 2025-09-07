#ifndef SignalOcafKernelPublisher_hpp
#define SignalOcafKernelPublisher_hpp

#include "AbstractOcafKernelPublisher.hpp"
#include "AbstractMessageBus.hpp"

#include <memory>
#include <vector>

class SignalOcafKernelPublisher : public AbstractOcafKernelPublisher {

    public:
    SignalOcafKernelPublisher(AbstractMessageBus& aMessageBus);
    
    void publishPrototypeAdded(DocLabel label) override;
    void publishPrototypeRemoved(DocLabel label) override;

    void publishPartAdded(DocLabel label) const override;
    void publishPartRemoved(DocLabel label) const override;
    void publishPartLocationChanged(DocLabel label) const override;
    void publishPartMarkerAttributeChanged(
        DocLabel label, AttributeType attributeEnum
    ) const override;

    void publishComponentAddedToAssembly(DocLabel compLabel) const override;
    void publishComponentRemovedFromAssembly(DocLabel label) const override;
   
    private:
    AbstractMessageBus& mMessageBus;
};

#endif