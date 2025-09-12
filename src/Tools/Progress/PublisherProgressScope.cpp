#include "PublisherProgressScope.hpp"
#include <algorithm>

PublisherProgressScope::PublisherProgressScope(
    const ProgressScopeId& id,
    std::shared_ptr<AbstractProgressPublisher> aProgressPublisher,
    double aWeight,
    PublisherProgressScope* aParent
) :
    mId(id),
    mPublisher(aProgressPublisher),
    mWeight(aWeight),
    mParent(aParent),
    mProgressFraction(0.0),
    mLaunched(false)
{}

void PublisherProgressScope::launch(const std::string& aMessage) {
    if (mLaunched) {
        reset();
    }
    mMessage = aMessage;
    mLaunched = true;
    mPublisher->scopeLaunched(mId, mMessage);
}

void PublisherProgressScope::advance(double aFraction) {
    mProgressFraction += aFraction;
    if (mProgressFraction >= 1.0) {
        mProgressFraction = 1.0;
        finalize();
        return;
    }

    mPublisher->scopeAdvanced(mId, mProgressFraction);

    if (mParent) {
        mParent->advance(aFraction * mWeight);
    }
}

void PublisherProgressScope::finalize() {
    finalizeAllChildren();

    mProgressFraction = 1.0;
    mPublisher->scopeFinalized(mId);

    if (mParent) {
        mParent->removeChild(mId);
    }
}

void PublisherProgressScope::reset() {
    mProgressFraction = 0.0;
    mLaunched = false;
    mMessage = "Default";
    mPublisher->scopeAdvanced(mId, mProgressFraction);

    for (auto& child : mActiveChildren) {
        child->reset();
    }
}

std::shared_ptr<AbstractProgressScope> PublisherProgressScope::newSubScope(
    const std::string& aMessage, double weight
) {
    auto childId = mId.spawnChild(mNextChildId++);
    auto child = std::make_shared<PublisherProgressScope>(
        childId, mPublisher, weight, this
    );
    
    child->launch(aMessage);
    mActiveChildren.push_back(child);
    return child;
}

void PublisherProgressScope::finalizeAllChildren() {
    for (auto& child : mActiveChildren) {
        child->finalize();
    }
    mActiveChildren.clear();
}

bool PublisherProgressScope::finalizeChild(const ProgressScopeId& aChildId) {
    auto it = std::find_if(
        mActiveChildren.begin(),
        mActiveChildren.end(),
        [&](const std::shared_ptr<AbstractProgressScope>& child) {
            return child->id() == aChildId;
        }
    );

    if (it != mActiveChildren.end()) {
        (*it)->finalize();
        mActiveChildren.erase(it);
        return true;
    }
    return false;
}

void PublisherProgressScope::removeChild(const ProgressScopeId& aChildId) {
    mActiveChildren.erase(
        std::remove_if(
            mActiveChildren.begin(),
            mActiveChildren.end(),
            [&](const std::shared_ptr<AbstractProgressScope>& child) {
                return child->id() == aChildId;
            }
        ),
        mActiveChildren.end()
    );
}