#include "ProgressRange.hpp"
#include <stdexcept>

ProgressRange::ProgressRange(const std::string& aLabel) : mLabel(aLabel) {}

ProgressRange::ProgressRange(
    ProgressRange* aParentRange,
    const std::string& aLabel,
    const Fraction& aWeightInParent
) : mParent(aParentRange), mLabel(aLabel), mWeightInParent(aWeightInParent){}

void ProgressRange::setLabel(const std::string& aLabel) {
    mLabel = aLabel;
}

void ProgressRange::setTo(const Fraction& aFraction) {
    auto diff  = aFraction.value() - mProgressFraction.value();
    advanceByFloat(diff);
}

void ProgressRange::advanceByFloat(float aFraction) {
    if(mFinalized){
        return;
    } 
    auto newFractionValue = mProgressFraction.value() + aFraction;
    mProgressFraction.set(newFractionValue);
    if (mProgressFraction.isOne()){
        finalize();
    }
    advanceParentByFloat(aFraction);
}

void ProgressRange::advanceBy(const Fraction& aFraction) {
    advanceByFloat(aFraction.value());
}

void ProgressRange::advanceParentByFloat(float aFraction) {
    if (mParent != nullptr){
        auto parentProgress = mWeightInParent.value() * aFraction;
        mParent->advanceByFloat(parentProgress);
    }
}

void ProgressRange::advanceParentBy(const Fraction& aFraction) {
    advanceParentByFloat(aFraction.value());
}

void ProgressRange::reset() {
    advanceByFloat(-mProgressFraction.value());
    mProgressFraction = Fraction(0.0f);
    mRemainingWeight = Fraction(1.0f);
    if(mChild){
        mChild->reset();
    }
    mFinalized = false;
}

void ProgressRange::finalize() {
    mFinalized = true;
    if(mChild){
        mChild->finalize();
    }
    advanceParentBy(mProgressFraction.toGo());
}

void ProgressRange::finalizeAndClearChild() {
    if (mChild){
        mChild->finalize();
        mChild.reset();
    }
}

ProgressRange& ProgressRange::newChild(
    const std::string& aLabel
) {
    return newChild(mRemainingWeight, aLabel);
}

ProgressRange& ProgressRange::newChild(
    const Fraction& aWeight,
    const std::string& aLabel
) {
    if (mChild){
        throw std::logic_error("Child already exists, only one child per range permitted. Clear child first.");
    }
    auto weight = aWeight;
    if (aWeight > mRemainingWeight) {
        weight = mRemainingWeight;
    }
   
    mChild = std::unique_ptr<ProgressRange>(
        new ProgressRange(this, aLabel, weight)
    );
    mRemainingWeight = mRemainingWeight - aWeight;
    return *mChild;
}

