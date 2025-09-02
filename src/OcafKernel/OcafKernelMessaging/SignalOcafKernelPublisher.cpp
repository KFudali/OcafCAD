#include "SignalOcafKernelPublisher.hpp"
#include "OcafKernelEvents.hpp"

SignalOcafKernelPublisher::SignalOcafKernelPublisher(AbstractMessageBus& aMessageBus)
    : mMessageBus(aMessageBus)
{}

void SignalOcafKernelPublisher::publishPrototypeAdded(PrototypeLabel label) {
    mMessageBus.publish<PrototypeAddedEvent>(PrototypeAddedEvent(label));
}

void SignalOcafKernelPublisher::publishPrototypeRemoved(PrototypeLabel label) {
    mMessageBus.publish<PrototypeRemovedEvent>(PrototypeRemovedEvent(label));
}

void SignalOcafKernelPublisher::publishPartAdded(PartLabel label) const {
    mMessageBus.publish<PartAddedEvent>(PartAddedEvent(label));
}

void SignalOcafKernelPublisher::publishPartRemoved(PartLabel label) const {
    mMessageBus.publish<PartRemovedEvent>(PartRemovedEvent(label));
}

void SignalOcafKernelPublisher::publishPartLocationChanged(PartLabel label) const {
    mMessageBus.publish<PartLocationChangedEvent>(PartLocationChangedEvent(label));
}

void SignalOcafKernelPublisher::publishPartAttributeChanged(
    PartLabel label, PartAttributeType attributeEnum
) const {
    mMessageBus.publish<PartAttributeChanged>(PartAttributeChanged(label, attributeEnum));
}

void SignalOcafKernelPublisher::publishComponentAddedToAssembly(PartLabel compLabel) const {
    mMessageBus.publish<ComponentAddedToAssemblyEvent>(ComponentAddedToAssemblyEvent(compLabel));
}

void SignalOcafKernelPublisher::publishComponentRemovedFromAssembly(PartLabel label) const {
    mMessageBus.publish<ComponentRemovedFromAssemblyEvent>(ComponentRemovedFromAssemblyEvent(label));
}
