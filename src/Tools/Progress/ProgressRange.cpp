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
    for (const auto& child : mChildren) {
        child->reset();
    }
    mFinalized = false;
}

void ProgressRange::finalize() {
    mFinalized = true;
    for (const auto& child : mChildren) {
        child->finalize();
    }
    advanceParentBy(mProgressFraction.toGo());
}

ProgressRange& ProgressRange::createSubRange(
    const std::string& aLabel
) {
    return createSubRange(aLabel, mRemainingWeight);
}

ProgressRange& ProgressRange::createSubRange(
    const std::string& aLabel,
    const Fraction& aWeight
) {
    auto weight = aWeight;
    if (aWeight > mRemainingWeight) {
        weight = mRemainingWeight;
    }
   
    auto child = std::unique_ptr<ProgressRange>(
        new ProgressRange(this, aLabel, weight)
    );
    mChildren.push_back(std::move(child));
    mRemainingWeight = mRemainingWeight - aWeight;
    return *mChildren.back();
}
