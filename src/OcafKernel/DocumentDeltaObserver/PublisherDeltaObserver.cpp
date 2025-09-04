#include "PublisherDeltaObserver.hpp"
#include "DocLabelUtils.hpp"


PublisherDeltaObserver::PublisherDeltaObserver(
    AbstractOcafKernelPublisher& aPublisher
) : mPublisher(aPublisher){}

bool PublisherDeltaObserver::setDocument(Handle(TDocStd_Document) aDoc) {
    mDocument = aDoc;
    return false;
};

bool PublisherDeltaObserver::processDelta(Handle(TDF_Delta) aDelta) const {
    if (aDelta.IsNull()) return false;
    TDF_AttributeDeltaList attributeDeltas = aDelta->AttributeDeltas();
    for (auto attrDelta : attributeDeltas){
        TDF_Label label = attrDelta->Label();
        if (DocLabelUtils::isRootAssemblyLabel(label)){
            continue;
        }
        if (DocLabelUtils::isPrototypeLabel(label)){

        } 
        if (DocLabelUtils::isPartLabel(label)){

        } 
    }
    return false;
};