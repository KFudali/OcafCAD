#ifndef AbstractOcafKernelObserver_hpp
#define AbstractOcafKernelObserver_hpp

#include "PrototypeLabel.hpp"
#include "PartLabel.hpp"
#include "PartAttributeType.hpp"

class AbstractOcafKernelObserver {
public:
    virtual ~AbstractOcafKernelObserver() = default;

    virtual void onPrototypeAdded(PrototypeLabel label) = 0;
    virtual void onPrototypeRemoved(PrototypeLabel label) = 0;
    
    virtual void onPartAdded(PartLabel label) = 0;
    virtual void onPartRemoved(PartLabel label) = 0;
    virtual void onPartLocationChanged(PartLabel label) = 0;
    virtual void onPartMarkerAttributeChanged(
        PartLabel label, AttributeType attributeEnum
    ) = 0;

    virtual void onComponentAddedToAssembly(PartLabel compLabel) = 0;
    virtual void onComponentRemovedFromAssembly(PartLabel label) = 0;
};

#endif
