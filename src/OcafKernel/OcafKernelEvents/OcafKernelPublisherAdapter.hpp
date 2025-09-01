#ifndef ConnectOcafObserver_hpp
#define ConnectOcafObserver_hpp

#include "OcafKernelConnections.hpp"
#include "AbstractOcafKernelObserver.hpp"
#include "SignalSubscription.hpp"

#include "OcafKernelSignalPublisher.hpp"
#include "OcafKernelEventTypes.hpp"

#include <boost/signals2.hpp>
#include <map>

namespace OcafKernelPublisherAdapter {

OcafKernelConnections connectOcafObserver(
    AbstractOcafKernelObserver& observer,
    OcafKernelSignalPublisher& publisher
) {
    OcafKernelConnections connections;

    // Prototype events
    connections.insert_or_assign(
        OcafKernelEventTypes::PrototypeAdded,
        SignalSubscription(publisher.mSignals.prototypeAdded.connect(
            [&](PrototypeLabel lbl){ observer.onPrototypeAdded(lbl); }))
    );

    connections.insert_or_assign(
        OcafKernelEventTypes::PrototypeRemoved,
        SignalSubscription(publisher.mSignals.prototypeRemoved.connect(
            [&](PrototypeLabel lbl){ observer.onPrototypeRemoved(lbl); }))
    );

    // Part events
    connections.insert_or_assign(
        OcafKernelEventTypes::PartAdded,
        SignalSubscription(publisher.mSignals.partAdded.connect(
            [&](PartLabel lbl){ observer.onPartAdded(lbl); }))
    );

    connections.insert_or_assign(
        OcafKernelEventTypes::PartRemoved,
        SignalSubscription(publisher.mSignals.partRemoved.connect(
            [&](PartLabel lbl){ observer.onPartRemoved(lbl); }))
    );

    connections.insert_or_assign(
        OcafKernelEventTypes::PartLocationChanged,
        SignalSubscription(publisher.mSignals.partLocationChanged.connect(
            [&](PartLabel lbl){ observer.onPartLocationChanged(lbl); }))
    );

    connections.insert_or_assign(
        OcafKernelEventTypes::PartAttributeChanged,
        SignalSubscription(publisher.mSignals.partAttributeChanged.connect(
            [&](PartLabel lbl, PartAttributeType attr){ 
                observer.onPartAttributeChanged(lbl, attr); 
            }))
    );

    // Assembly component events
    connections.insert_or_assign(
        OcafKernelEventTypes::ComponentAddedToAssembly,
        SignalSubscription(publisher.mSignals.componentAddedToAssembly.connect(
            [&](PartLabel lbl){ observer.onComponentAddedToAssembly(lbl); }))
    );

    connections.insert_or_assign(
        OcafKernelEventTypes::ComponentRemovedFromAssembly,
        SignalSubscription(publisher.mSignals.componentRemovedFromAssembly.connect(
            [&](PartLabel lbl){ observer.onComponentRemovedFromAssembly(lbl); }))
    );

    return connections;
}

} // namespace OcafKernelPublisherAdapter

#endif
