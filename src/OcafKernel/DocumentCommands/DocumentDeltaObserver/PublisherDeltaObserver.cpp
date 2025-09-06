#include "PublisherDeltaObserver.hpp"
#include "DocLabelUtils.hpp"

#include <Standard_Type.hxx>
#include <TDF_DeltaOnAddition.hxx>

PublisherDeltaObserver::PublisherDeltaObserver(
    AbstractOcafKernelPublisher& aPublisher
) : mPublisher(aPublisher){}

bool PublisherDeltaObserver::setDocument(Handle(TDocStd_Document) aDoc) {
    if (!mDocument.IsNull()){
        return false;
    }
    mDocument = aDoc;
    return true;
};

bool PublisherDeltaObserver::processDelta(Handle(TDF_Delta) aDelta) const {
    if (aDelta.IsNull()) return false;
    TDF_AttributeDeltaList attributeDeltas = aDelta->AttributeDeltas();
    TDF_LabelList labelsInDelta;
    aDelta->Labels(labelsInDelta);


    for (auto attrDelta : attributeDeltas){
        auto label = attrDelta->Label();
        auto isAddition = attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnAddition));
        auto null = label.IsNull();
        auto docLabel = DocLabel(label);
        auto labelStr = docLabel.toString();
        
        if (DocLabelUtils::isPrototypeLabel(label) && attrDelta){
            mPublisher.publishPrototypeAdded(PrototypeLabel(label));
        } 
    }
    return false;
};