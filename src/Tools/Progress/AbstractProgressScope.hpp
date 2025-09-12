#ifndef AbstractProgressScope_hpp
#define AbstractProgressScope_hpp

#include <memory>
#include <string>
#include <vector>
#include "ProgressScopeId.hpp"

class AbstractProgressScope {
    public:
    virtual ~AbstractProgressScope() = default;

    virtual ProgressScopeId id() const = 0;    

    virtual std::string message() const = 0;
    virtual double progressFraction() const = 0;


    virtual void launch(const std::string& aMessage) = 0;
    virtual void advance(double aFraction) = 0;
    virtual void finalize() = 0;
    virtual void reset() = 0;

    virtual std::shared_ptr<AbstractProgressScope> newSubScope(
        const std::string& aScopeLabel, double weight
    ) = 0;
    virtual AbstractProgressScope* parentScope() = 0;
    virtual const std::vector<std::shared_ptr<AbstractProgressScope>>& activeChildren() = 0;
    virtual void finalizeAllChildren() = 0;
    virtual bool finalizeChild(const ProgressScopeId& aChildId) = 0;
};

#endif