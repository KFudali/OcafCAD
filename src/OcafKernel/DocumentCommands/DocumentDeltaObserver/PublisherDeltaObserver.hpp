#ifndef PublisherDeltaObserver_hpp
#define PublisherDeltaObserver_hpp

#include "AbstractDeltaObserver.hpp"
#include "AbstractOcafKernelPublisher.hpp"

#include <TDF_Delta.hxx>
#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>

class PublisherDeltaObserver : public AbstractDeltaObserver{
public:
    PublisherDeltaObserver(
        AbstractOcafKernelPublisher& aPublisher
    );
   
    bool setDocument(Handle(TDocStd_Document) aDocument) override;
    bool processDelta(Handle(TDF_Delta) aDelta) const override;

private:

    void processAddition(Handle(TDF_DeltaOnAddition) aAttrDelta) const;
    void processRemoval(Handle(TDF_DeltaOnRemoval) aAttrDelta) const;
    void processForget(Handle(TDF_DeltaOnForget) aAttrDelta) const;
    void processResume(Handle(TDF_DeltaOnResume) aAttrDelta) const;
    void processModification(Handle(TDF_DeltaOnModification) aAttrDelta) const;

    AbstractOcafKernelPublisher& mPublisher;
    Handle(TDocStd_Document) mDocument;
};

#endif