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
    AbstractOcafKernelPublisher& mPublisher;
    Handle(TDocStd_Document) mDocument;
};

#endif