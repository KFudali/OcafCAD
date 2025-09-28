#include "SignalOcafKernelPublisher.hpp"
#include "OcafKernelEvents.hpp"

SignalOcafKernelPublisher::SignalOcafKernelPublisher(AbstractMessageBus& aMessageBus)
    : mMessageBus(aMessageBus)
{}

void SignalOcafKernelPublisher::publishPrototypeAdded(DocLabel label) {
    mMessageBus.publish<PrototypeAddedEvent>(PrototypeAddedEvent(label));
}

void SignalOcafKernelPublisher::publishPrototypeRemoved(DocLabel label) {
    mMessageBus.publish<PrototypeRemovedEvent>(PrototypeRemovedEvent(label));
}

void SignalOcafKernelPublisher::publishPartAdded(DocLabel label) const {
    mMessageBus.publish<PartAddedEvent>(PartAddedEvent(label));
}

void SignalOcafKernelPublisher::publishPartRemoved(DocLabel label) const {
    mMessageBus.publish<PartRemovedEvent>(PartRemovedEvent(label));
}

void SignalOcafKernelPublisher::publishPartLocationChanged(DocLabel label) const {
    mMessageBus.publish<PartLocationChangedEvent>(PartLocationChangedEvent(label));
}

void SignalOcafKernelPublisher::publishPartAttributeChanged(
    DocLabel label, AttributeType attributeEnum
) const {
    mMessageBus.publish<PartAttributeChanged>(PartAttributeChanged(label, attributeEnum));
}

void SignalOcafKernelPublisher::publishComponentAddedToAssembly(DocLabel compLabel) const {
    mMessageBus.publish<ComponentAddedToAssemblyEvent>(ComponentAddedToAssemblyEvent(compLabel));
}

void SignalOcafKernelPublisher::publishComponentRemovedFromAssembly(DocLabel label) const {
    mMessageBus.publish<ComponentRemovedFromAssemblyEvent>(ComponentRemovedFromAssemblyEvent(label));
}
