#ifndef PublisherProgressScope_hpp
#define PublisherProgressScope_hpp

#include "AbstractProgressScope.hpp"
#include "AbstractProgressPublisher.hpp"

class PublisherProgressScope : public AbstractProgressScope {
public: 
    PublisherProgressScope(
        const ProgressScopeId& aId,
        std::shared_ptr<AbstractProgressPublisher> aProgressPublisher,
        double aWeight = 1.0,
        PublisherProgressScope* aParent = nullptr
    );

    inline ProgressScopeId id() const override { return mId; }
    inline std::string message() const override { return mMessage; }
    inline double progressFraction() const override { return mProgressFraction; }

    void launch(const std::string& aMessage) override;
    void advance(double aFraction) override;
    void finalize() override;
    void reset() override;

    std::shared_ptr<AbstractProgressScope> newSubScope(
        const std::string& aScopeLabel, double weight
    ) override;

    inline AbstractProgressScope* parentScope() override { return mParent; }
    const std::vector<std::shared_ptr<AbstractProgressScope>>& activeChildren(){
        return mActiveChildren;
    };

    void finalizeAllChildren() override;    
    bool finalizeChild(const ProgressScopeId& aChildId) override;

private:
    void removeChild(const ProgressScopeId& aChildId);

    
    ProgressScopeId mId;
    int mNextChildId = 1;

    bool mLaunched = false;
    double mProgressFraction = 0.0;
    double mWeight = 1.0;
    std::string mMessage = "Default";
    
    PublisherProgressScope* mParent;
    std::vector<std::shared_ptr<AbstractProgressScope>> mActiveChildren;
    std::shared_ptr<AbstractProgressPublisher> mPublisher;
};

#endif
