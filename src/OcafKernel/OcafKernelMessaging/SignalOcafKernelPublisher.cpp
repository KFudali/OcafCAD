#include "SignalOcafKernelPublisher.hpp"

#include "PrototypeEvents.hpp"
#include "PartEvents.hpp"
#include "AssemblyEvents.hpp"

SignalOcafKernelPublisher::SignalOcafKernelPublisher(AbstractMessageBus& aMessageBus)
    : mMessageBus(aMessageBus)
{}

void SignalOcafKernelPublisher::publishPrototypeAdded(PrototypeLabel label) {
    mMessageBus.publish(PrototypeAddedEvent(label));
}

void SignalOcafKernelPublisher::publishPrototypeRemoved(PrototypeLabel label) {
    mMessageBus.publish(PrototypeRemovedEvent(label));
}

void SignalOcafKernelPublisher::publishPartAdded(PartLabel label) const {
    mMessageBus.publish(PartAddedEvent(label));
}

void SignalOcafKernelPublisher::publishPartRemoved(PartLabel label) const {
    mMessageBus.publish(PartAddedRemoved(label));
}

void SignalOcafKernelPublisher::publishPartLocationChanged(PartLabel label) const {
    mMessageBus.publish(PartLocationChangedEvent(label));
}

void SignalOcafKernelPublisher::publishPartAttributeChanged(
    PartLabel label, PartAttributeType attributeEnum
) const {
    mMessageBus.publish(PartAttributeChanged(label, attributeEnum));
}

void SignalOcafKernelPublisher::publishComponentAddedToAssembly(PartLabel compLabel) const {
    mMessageBus.publish(ComponentAddedToAssemblyEvent(compLabel));
}

void SignalOcafKernelPublisher::publishComponentRemovedFromAssembly(PartLabel label) const {
    mMessageBus.publish(ComponentRemovedFromAssemblyEvent(label));
}