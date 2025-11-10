#include "GeometryDeltaObserver.hpp"

#include "DocLabel.hpp"
#include "DocLabelUtils.hpp"

#include "PartEvents.hpp"
#include "AssemblyEvents.hpp"
#include "PrototypeEvents.hpp"

#include "PartMarkerAttribute.hpp"
#include "ShapeMarkerAttribute.hpp"

GeometryDeltaObserver::GeometryDeltaObserver(MessagePublisher& aMessagePublisher)
    : mMessagePublisher(aMessagePublisher) {}

void GeometryDeltaObserver::onAddition(Handle(TDF_DeltaOnAddition) aDelta) {
    if (aDelta.IsNull() || aDelta->Attribute().IsNull()) return;
    auto label = aDelta->Label();

    if (aDelta->Attribute()->IsKind(STANDARD_TYPE(ShapeMarkerAttribute))) {
        mMessagePublisher.publish(PrototypeAddedEvent(DocLabel(label)));
    }
    else if (aDelta->Attribute()->IsKind(STANDARD_TYPE(PartMarkerAttribute))) {
        mMessagePublisher.publish(PartAddedEvent(DocLabel(label)));
        if (label.IsNull()) {return;}
        if (!DocLabelUtils::isRootAssemblyLabel(label.Father())) {
            mMessagePublisher.publish(ComponentAddedToAssemblyEvent(DocLabel(label)));
        }
    }
}

void GeometryDeltaObserver::onRemoval(Handle(TDF_DeltaOnRemoval) aDelta) {
    if (aDelta.IsNull() || aDelta->Attribute().IsNull()) return;
    auto label = aDelta->Label();

    if (aDelta->Attribute()->IsKind(STANDARD_TYPE(ShapeMarkerAttribute))) {
        mMessagePublisher.publish(PrototypeRemovedEvent(DocLabel(label)));
    }
    else if (aDelta->Attribute()->IsKind(STANDARD_TYPE(PartMarkerAttribute))) {
        mMessagePublisher.publish(PartRemovedEvent(DocLabel(label)));
        if (label.IsNull()) {return;}
        if (!DocLabelUtils::isRootAssemblyLabel(label.Father())) {
            mMessagePublisher.publish(ComponentRemovedFromAssemblyEvent(DocLabel(label)));
        }
    }
}

void GeometryDeltaObserver::onForget(Handle(TDF_DeltaOnForget) aDelta) {
    if (aDelta.IsNull() || aDelta->Attribute().IsNull()) return;
    auto label = aDelta->Label();

    if (aDelta->Attribute()->IsKind(STANDARD_TYPE(ShapeMarkerAttribute))) {
        mMessagePublisher.publish(PrototypeRemovedEvent(DocLabel(label)));
    }
    else if (aDelta->Attribute()->IsKind(STANDARD_TYPE(PartMarkerAttribute))) {
        mMessagePublisher.publish(PartRemovedEvent(DocLabel(label)));
    }
}

void GeometryDeltaObserver::onResume(Handle(TDF_DeltaOnResume) aDelta) {
    if (aDelta.IsNull() || aDelta->Attribute().IsNull()) return;
    auto label = aDelta->Label();

    if (aDelta->Attribute()->IsKind(STANDARD_TYPE(ShapeMarkerAttribute))) {
        mMessagePublisher.publish(PrototypeAddedEvent(DocLabel(label)));
    }
    else if (aDelta->Attribute()->IsKind(STANDARD_TYPE(PartMarkerAttribute))) {
        mMessagePublisher.publish(PartAddedEvent(DocLabel(label)));
    }
}

void GeometryDeltaObserver::onModification(Handle(TDF_DeltaOnModification) aDelta) {
    if (aDelta.IsNull() || aDelta->Attribute().IsNull()) return;
    // TODO: detect which attribute changed and publish PartAttributeChanged, PartLocationChangedEvent, etc.
}
