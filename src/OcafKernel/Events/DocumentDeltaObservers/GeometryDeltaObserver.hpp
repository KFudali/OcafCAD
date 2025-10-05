#ifndef GeometryDeltaObserver_hpp
#define GeometryDeltaObserver_hpp

#include "AbstractDeltaObserver.hpp"
#include "MessagePublisher.hpp"

class GeometryDeltaObserver : public AbstractDeltaObserver {
    public:
    GeometryDeltaObserver(MessagePublisher& aMessagePublisher);
    
    void onAddition(Handle(TDF_DeltaOnAddition) aDelta) override;
    void onRemoval(Handle(TDF_DeltaOnRemoval) aDelta) override;
    void onForget(Handle(TDF_DeltaOnForget) aDelta) override;
    void onResume(Handle(TDF_DeltaOnResume) aDelta) override;
    void onModification(Handle(TDF_DeltaOnModification) aDelta) override;

    private:
    MessagePublisher& mMessagePublisher;

};

#endif