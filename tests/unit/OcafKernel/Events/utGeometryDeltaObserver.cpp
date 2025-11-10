#include <gmock/gmock.h>

#include <TDF_DefaultDeltaOnModification.hxx>
#include <TDF_DefaultDeltaOnRemoval.hxx>

#include "PrototypeEvents.hpp"
#include "AssemblyEvents.hpp"
#include "PartEvents.hpp"
#include "PartMarkerAttribute.hpp"
#include "ShapeMarkerAttribute.hpp"

#include "GeometryDeltaObserver.hpp"
#include "MockMessageBus.hpp"

using ::testing::_;

class GeometryObserverTest : public ::testing::Test {
   protected:
    void SetUp() override {
        observer = std::make_unique<GeometryDeltaObserver>(publisher);
    }

    MockMessageBus mockBus;
    MessagePublisher publisher{mockBus};
    std::unique_ptr<GeometryDeltaObserver> observer;
};

TEST_F(GeometryObserverTest, PrototypeAdditionPublishesCorrectEvent) {
    Handle(ShapeMarkerAttribute) attr = new ShapeMarkerAttribute();
    Handle(TDF_DeltaOnAddition) delta(new TDF_DeltaOnAddition(attr));

    EXPECT_CALL(mockBus,
                publishImpl(std::type_index(typeid(PrototypeAddedEvent)), _))
        .Times(1);
    observer->onAddition(delta);
}

TEST_F(GeometryObserverTest, PrototypeRemovalPublishesCorrectEvent) {
    Handle(ShapeMarkerAttribute) attr = new ShapeMarkerAttribute();
    Handle(TDF_DeltaOnRemoval) delta(new TDF_DefaultDeltaOnRemoval(attr));

    EXPECT_CALL(mockBus,
                publishImpl(std::type_index(typeid(PrototypeRemovedEvent)), _))
        .Times(1);
    observer->onRemoval(delta);
}

TEST_F(GeometryObserverTest, PrototypeForgetPublishesCorrectEvent) {
    Handle(ShapeMarkerAttribute) attr = new ShapeMarkerAttribute();
    Handle(TDF_DeltaOnForget) delta(new TDF_DeltaOnForget(attr));

    EXPECT_CALL(mockBus,
                publishImpl(std::type_index(typeid(PrototypeRemovedEvent)), _))
        .Times(1);
    observer->onForget(delta);
}

TEST_F(GeometryObserverTest, PrototypeResumePublishesCorrectEvent) {
    Handle(ShapeMarkerAttribute) attr = new ShapeMarkerAttribute();
    Handle(TDF_DeltaOnResume) delta(new TDF_DeltaOnResume(attr));

    EXPECT_CALL(mockBus,
                publishImpl(std::type_index(typeid(PrototypeAddedEvent)), _))
        .Times(1);
    observer->onResume(delta);
}

TEST_F(GeometryObserverTest, PrototypeModificationPublishesNothing) {
    Handle(ShapeMarkerAttribute) attr = new ShapeMarkerAttribute();
    Handle(TDF_DeltaOnModification)
        delta(new TDF_DefaultDeltaOnModification(attr));

    EXPECT_CALL(mockBus, publishImpl(_, _)).Times(0);
    observer->onModification(delta);
}

TEST_F(GeometryObserverTest, PartAdditionPublishesCorrectEvent) {
    Handle(PartMarkerAttribute) attr = new PartMarkerAttribute();
    Handle(TDF_DeltaOnAddition) delta(new TDF_DeltaOnAddition(attr));

    EXPECT_CALL(mockBus,
                publishImpl(std::type_index(typeid(PartAddedEvent)), _))
        .Times(1);
    observer->onAddition(delta);
}

TEST_F(GeometryObserverTest, PartRemovalPublishesCorrectEvent) {
    Handle(PartMarkerAttribute) attr = new PartMarkerAttribute();
    Handle(TDF_DeltaOnRemoval) delta(new TDF_DefaultDeltaOnRemoval(attr));

    EXPECT_CALL(mockBus,
                publishImpl(std::type_index(typeid(PartRemovedEvent)), _))
        .Times(1);
    observer->onRemoval(delta);
}

TEST_F(GeometryObserverTest, PartForgetPublishesCorrectEvent) {
    Handle(PartMarkerAttribute) attr = new PartMarkerAttribute();
    Handle(TDF_DeltaOnForget) delta(new TDF_DeltaOnForget(attr));

    EXPECT_CALL(mockBus,
                publishImpl(std::type_index(typeid(PartRemovedEvent)), _))
        .Times(1);
    observer->onForget(delta);
}

TEST_F(GeometryObserverTest, PartResumePublishesCorrectEvent) {
    Handle(PartMarkerAttribute) attr = new PartMarkerAttribute();
    Handle(TDF_DeltaOnResume) delta(new TDF_DeltaOnResume(attr));

    EXPECT_CALL(mockBus,
                publishImpl(std::type_index(typeid(PartAddedEvent)), _))
        .Times(1);
    observer->onResume(delta);
}

TEST_F(GeometryObserverTest, PartModificationPublishesNothing) {
    Handle(PartMarkerAttribute) attr = new PartMarkerAttribute();
    Handle(TDF_DeltaOnModification)
        delta(new TDF_DefaultDeltaOnModification(attr));

    EXPECT_CALL(mockBus, publishImpl(_, _)).Times(0);
    observer->onModification(delta);
}
