#include "PublisherDeltaObserver.hpp"
#include "DocLabelUtils.hpp"

#include <Standard_Type.hxx>
#include <TDF_DeltaOnAddition.hxx>
#include <TDF_DeltaOnRemoval.hxx>
#include <TDF_DeltaOnModification.hxx>
#include <TDF_DeltaOnResume.hxx>
#include <TDF_DeltaOnForget.hxx>

#include "PartMarkerAttribute.hpp"
#include "PrototypeMarkerAttribute.hpp"

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

    for (auto& attrDelta : attributeDeltas) {
        if (attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnAddition))) {
            processAddition(Handle(TDF_DeltaOnAddition)::DownCast(attrDelta));
        } 
        else if (attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnRemoval))) {
            processRemoval(Handle(TDF_DeltaOnRemoval)::DownCast(attrDelta));
        } 
        else if (attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnForget))) {
            processForget(Handle(TDF_DeltaOnForget)::DownCast(attrDelta));
        }
        else if (attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnResume))) {
            processResume(Handle(TDF_DeltaOnResume)::DownCast(attrDelta));
        }
        else if (attrDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnModification))) {
            processModification(Handle(TDF_DeltaOnModification)::DownCast(attrDelta));
        }
    }
    return true;
}

void PublisherDeltaObserver::processAddition(
    Handle(TDF_DeltaOnAddition) aAttrDelta
) const{
    auto label = aAttrDelta->Label();
    if (aAttrDelta->Attribute()->IsKind(STANDARD_TYPE(PrototypeMarkerAttribute))){
        mPublisher.publishPrototypeAdded(DocLabel(label));
    } 
    if (aAttrDelta->Attribute()->IsKind(STANDARD_TYPE(PartMarkerAttribute))){
        mPublisher.publishPartAdded(DocLabel(label));
        if (!DocLabelUtils::isRootAssemblyLabel(label.Father())){
            mPublisher.publishComponentAddedToAssembly(DocLabel(label));
        }
    } 
}

void PublisherDeltaObserver::processRemoval(
    Handle(TDF_DeltaOnRemoval) aAttrDelta
) const{
    auto label = aAttrDelta->Label();
    if (aAttrDelta->Attribute()->IsKind(STANDARD_TYPE(PrototypeMarkerAttribute))){
        mPublisher.publishPrototypeRemoved(DocLabel(label));
    } 
    if (aAttrDelta->Attribute()->IsKind(STANDARD_TYPE(PartMarkerAttribute))){
        mPublisher.publishPartRemoved(DocLabel(label));
        if (!DocLabelUtils::isRootAssemblyLabel(label.Father())){
            mPublisher.publishComponentRemovedFromAssembly(DocLabel(label));
        }
    } 
}
void PublisherDeltaObserver::processForget(
    Handle(TDF_DeltaOnForget) aAttrDelta
) const{
    auto label = aAttrDelta->Label();
    if (aAttrDelta->Attribute()->IsKind(STANDARD_TYPE(PrototypeMarkerAttribute))){
        mPublisher.publishPrototypeRemoved(DocLabel(label));
    } 
    if (aAttrDelta->Attribute()->IsKind(STANDARD_TYPE(PartMarkerAttribute))){
        mPublisher.publishPartRemoved(DocLabel(label));
    } 
}

void PublisherDeltaObserver::processResume(
    Handle(TDF_DeltaOnResume) aAttrDelta
) const{
    auto label = aAttrDelta->Label();
    if (aAttrDelta->Attribute()->IsKind(STANDARD_TYPE(PrototypeMarkerAttribute))){
        mPublisher.publishPrototypeAdded(DocLabel(label));
    } 
    if (aAttrDelta->Attribute()->IsKind(STANDARD_TYPE(PartMarkerAttribute))){
        mPublisher.publishPartAdded(DocLabel(label));
    } 
}

void PublisherDeltaObserver::processModification(
    Handle(TDF_DeltaOnModification) aAttrDelta
) const{}