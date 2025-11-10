#include "RefTreeLabel.hpp"
#include "RefTreeMarkerAttribute.hpp"

#include <TDF_Attribute.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Reference.hxx>

RefTreeLabel::RefTreeLabel(
    const TDF_Label& aParentLabel,
    const TDF_LabelSequence& aRefs
) :  DocLabel(aParentLabel.NewChild()) {
    Handle(RefTreeMarkerAttribute) markerAttr = new RefTreeMarkerAttribute();
    mLabel.AddAttribute(markerAttr);
    for (const auto ref : aRefs){
        addRef(ref);
    }
}

TDF_Label RefTreeLabel::addRef(const TDF_Label& aRefLabel){
    auto label = mLabel.NewChild();
    Handle(TDF_Reference) refAttr = new TDF_Reference();
    refAttr->Set(aRefLabel);
    label.AddAttribute(refAttr);
    return label;
}

RefTreeLabel::RefTreeLabel(TDF_Label aRefTreeLabel){
    mLabel = aRefTreeLabel;
    Handle(RefTreeMarkerAttribute) markerAttr;
    if (!mLabel.FindAttribute(RefTreeMarkerAttribute::GetID(), markerAttr)){
        throw LabelException(
            "Cannot create. Label is missing RefTreeMarkerAttribute."
        );
    }
}

TDF_LabelSequence RefTreeLabel::references() const {
    TDF_LabelSequence seq;
    for (TDF_ChildIterator it(mLabel); it.More(); it.Next()) {
        TDF_Label child = it.Value();
        Handle(TDF_Reference) refAttr;
        if (child.FindAttribute(TDF_Reference::GetID(), refAttr)) {
            seq.Append(refAttr->Get());
        }
    }
    return seq;
}

bool RefTreeLabel::removeReference(const TDF_Label& aRefLabel){
    for (TDF_ChildIterator it(mLabel); it.More(); it.Next()) {
        TDF_Label child = it.Value();
        Handle(TDF_Reference) refAttr;
        if (child.FindAttribute(TDF_Reference::GetID(), refAttr)) {
            if(refAttr->Get().IsEqual(aRefLabel)){
                child.ForgetAllAttributes();
                return true;
            }
        }
    }
    return false;
}

bool RefTreeLabel::appendReference(const TDF_Label& aRefLabel){
    auto refs = references();
    if (std::find(refs.begin(), refs.end(), aRefLabel) != refs.end()){
        return false;
    }
    addRef(aRefLabel);
    return true;
}