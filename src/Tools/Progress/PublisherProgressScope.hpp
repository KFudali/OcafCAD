#ifndef PublisherProgressScope_hpp
#define PublisherProgressScope_hpp

#include "AbstractProgressScope.hpp"
#include "AbstractProgressPublisher.hpp"

class PublisherProgressScope : public AbstractProgressScope {
public: 
    PublisherProgressScope(
        const ProgressScopeId& aId,
        const std::string& aMessage,
        std::shared_ptr<AbstractProgressPublisher> aProgressPublisher,
        double aWeight = 1.0,
        PublisherProgressScope* aParent = nullptr
    );

    inline ProgressScopeId id() const override { return _id; }
    inline std::string message() const override { return _message; }
    inline double progressFraction() const override { return _progressFraction; }

    void advance(double aFraction) override;
    void finalize() override;
    void reset() override;

    AbstractProgressScope& newSubScope(
        const std::string& aScopeLabel, double weight
    ) override;

    inline AbstractProgressScope* parentScope() override { return _parent; }

    void finalizeAllChildren() override;    
    bool finalizeChild(const ProgressScopeId& aChildId) override;

private:
    void removeChild(const ProgressScopeId& aChildId);

    double _progressFraction = 0.0;
    double _weight;

    ProgressScopeId _id;
    PublisherProgressScope* _parent = nullptr;
    std::string _message = "Processing...";
    std::vector<std::unique_ptr<PublisherProgressScope>> _children;
    int _nextChildId = 1;
    std::shared_ptr<AbstractProgressPublisher> _publisher;
};

#endif
