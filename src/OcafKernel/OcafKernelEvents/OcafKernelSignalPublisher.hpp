#ifndef OcafKernelPublisher_hpp
#define OcafKernelPublisher_hpp

#include "AbstractOcafKernelPublisher.hpp"
#include "AbstractOcafKernelObserver.hpp"

#include <memory>
#include <vector>

#include <boost/signals2.hpp>
#include "OcafKernelEventTypes.hpp"

struct OcafKernelSignals {
    boost::signals2::signal<void (PrototypeLabel)> prototypeAdded;
    boost::signals2::signal<void (PrototypeLabel)> prototypeRemoved;
    boost::signals2::signal<void (PartLabel)> partAdded;
    boost::signals2::signal<void (PartLabel)> partRemoved;
    boost::signals2::signal<void (PartLabel)> partLocationChanged;
    boost::signals2::signal<void (PartLabel, PartAttributeType)> partAttributeChanged;
    boost::signals2::signal<void (PartLabel)> componentAddedToAssembly;
    boost::signals2::signal<void (PartLabel)> componentRemovedFromAssembly;
};

class OcafKernelSignalPublisher : public AbstractOcafKernelPublisher {

    public:
    OcafKernelSignalPublisher() = default;
    void publishPrototypeAdded(PrototypeLabel label) override { 
        mSignals.prototypeAdded(label); 
    }
    void publishPrototypeRemoved(PrototypeLabel label) override { 
        mSignals.prototypeRemoved(label); 
    }
    void publishPartAdded(PartLabel label) const override { 
        mSignals.partAdded(label); 
    }
    void publishPartRemoved(PartLabel label) const override { 
        mSignals.partRemoved(label); 
    }
    void publishPartLocationChanged(PartLabel label) const override { 
        mSignals.partLocationChanged(label); 
    }
    void publishPartAttributeChanged(
        PartLabel label, 
        PartAttributeType attributeEnum
    ) const override {
        mSignals.partAttributeChanged(label, attributeEnum);
    }
    void publishComponentAddedToAssembly(PartLabel compLabel) const override { 
        mSignals.componentAddedToAssembly(compLabel); 
    }
    void publishComponentRemovedFromAssembly(PartLabel label) const override { 
        mSignals.componentRemovedFromAssembly(label); 
    }
    
    OcafKernelSignals mSignals;
};

#endif