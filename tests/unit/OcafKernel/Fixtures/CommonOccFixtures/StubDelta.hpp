#ifndef StubDeltas_hpp
#define StubDeltas_hpp

#include <TDF_Delta.hxx>
#include <TDF_DeltaOnAddition.hxx>
#include <TDF_DefaultDeltaOnRemoval.hxx>
#include <TDF_DeltaOnForget.hxx>
#include <TDF_DeltaOnResume.hxx>
#include <TDF_DefaultDeltaOnModification.hxx>
#include <TDF_Attribute.hxx>
#include <TDF_Label.hxx>

#include "StubAttribute.hpp"

class TestTDF_Delta : public TDF_Delta {
public:
    void exposeAdd(const Handle(TDF_AttributeDelta)& ad) { AddAttributeDelta(ad); }
};

struct StubDeltas {
    static Handle(TDF_Delta) makeAdditionDelta() {
        Handle(TestTDF_Delta) delta = new TestTDF_Delta();
        Handle(StubAttribute) attr = StubAttribute::New();
        Handle(TDF_AttributeDelta) addition = new TDF_DeltaOnAddition(attr);
        delta->exposeAdd(addition);
        return delta;
    }

    static Handle(TDF_Delta) makeRemovalDelta() {
        Handle(TestTDF_Delta) delta = new TestTDF_Delta();
        Handle(StubAttribute) attr = StubAttribute::New();
        Handle(TDF_AttributeDelta) removal = new TDF_DefaultDeltaOnRemoval(attr);
        delta->exposeAdd(removal);
        return delta;
    }

    static Handle(TDF_Delta) makeForgetDelta() {
        Handle(TestTDF_Delta) delta = new TestTDF_Delta();
        Handle(StubAttribute) attr = StubAttribute::New();
        Handle(TDF_AttributeDelta) forget = new TDF_DeltaOnForget(attr);
        delta->exposeAdd(forget);
        return delta;
    }

    static Handle(TDF_Delta) makeResumeDelta() {
        Handle(TestTDF_Delta) delta = new TestTDF_Delta();
        Handle(StubAttribute) attr = StubAttribute::New();
        Handle(TDF_AttributeDelta) resume = new TDF_DeltaOnResume(attr);
        delta->exposeAdd(resume);
        return delta;
    }

    static Handle(TDF_Delta) makeModificationDelta() {
        Handle(TestTDF_Delta) delta = new TestTDF_Delta();
        Handle(StubAttribute) attr = StubAttribute::New();
        Handle(TDF_AttributeDelta) modification = new TDF_DefaultDeltaOnModification(attr);
        delta->exposeAdd(modification);
        return delta;
    }
};

#endif
