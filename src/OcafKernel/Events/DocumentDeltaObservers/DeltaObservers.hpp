#ifndef DeltaObservers_hpp
#define DeltaObservers_hpp

#include "AbstractMessageBus.hpp"
#include "GeometryDeltaObserver.hpp"

class DeltaObservers {
    public:
    DeltaObservers(
        AbstractMessageBus& aMessageBus
    ) : mMessagePublisher(aMessageBus),
        mGeometryObserver(mMessagePublisher) {}

    GeometryDeltaObserver* geometry() {return &mGeometryObserver;};    

    private:
    MessagePublisher mMessagePublisher;
    GeometryDeltaObserver mGeometryObserver;
};


#endif