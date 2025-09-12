#include "PublisherProgressScope.hpp"

PublisherProgressScope::PublisherProgressScope(
    const ProgressScopeId& id,
    const std::string& aMessage,
    std::shared_ptr<AbstractProgressPublisher> aProgressPublisher,
    double aWeight,
    PublisherProgressScope* aParent
) :
    _id(id),
    _message(aMessage),
    _publisher(std::move(aProgressPublisher)),
    _weight(aWeight),
    _parent(aParent),
    _progressFraction(0.0)
{}

void PublisherProgressScope::advance(double aFraction) {
    if (aFraction >= 1.0) {
        _progressFraction = 1.0;
        finalize();
        return;
    }
    _progressFraction = aFraction;
    _publisher->scopeAdvanced(_id, _progressFraction);

    if (_parent) {
        auto parentProgress = _progressFraction * _weight;
        _parent->advance(parentProgress);
    }
}

void PublisherProgressScope::finalize() {
    _publisher->scopeFinalized(_id);
    _progressFraction = 1.0;
    if (_parent) {
        _parent->removeChild(_id);
    }
}

void PublisherProgressScope::reset() {
    _progressFraction = 0.0;
    _publisher->scopeAdvanced(_id, _progressFraction);
}

AbstractProgressScope& PublisherProgressScope::newSubScope(
    const std::string& aMessage, double weight
) {
    auto childId = _id.spawnChild(_nextChildId++);
    auto child = std::make_unique<PublisherProgressScope>(
        childId, aMessage, _publisher, weight, this
    );
    auto& ref = *child;
    _children.push_back(std::move(child));
    return ref;
}

void PublisherProgressScope::finalizeAllChildren() {
    for (auto& child : _children) {
        child->finalize();
    }
    _children.clear();
}

bool PublisherProgressScope::finalizeChild(const ProgressScopeId& aChildId) {
    for (auto& child : _children) {
        if (child->id() == aChildId) {
            child->finalize();
            removeChild(aChildId);
            return true;
        }
    }
    return false;
}

void PublisherProgressScope::removeChild(const ProgressScopeId& aChildId) {
    _children.erase(
        std::remove_if(
            _children.begin(), _children.end(),
            [&](const std::unique_ptr<PublisherProgressScope>& child) {
                return child->id() == aChildId;
            }
        ),
        _children.end()
    );
}
