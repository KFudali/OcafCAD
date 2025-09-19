#ifndef StubProgressScope_hpp
#define StubProgressScope_hpp

#include <memory>
#include "SignalMessageBus.hpp"
#include "EventProgressPublisher.hpp"
#include "PublisherProgressScope.hpp"

class StubProgressScopeFactory {
   public:
    StubProgressScopeFactory(){
        mBus = std::make_unique<SignalMessageBus>();
        auto pub = std::make_unique<MessagePublisher>(*mBus);
        mPub = std::make_shared<EventProgressPublisher>(std::move(pub));
    }

    std::unique_ptr<AbstractProgressScope> scope() {
        ProgressScopeId id(std::vector<int>{1,2,3});
        return std::move(std::make_unique<PublisherProgressScope>(id, mPub));
    };    

    private:
    std::unique_ptr<SignalMessageBus> mBus;
    std::shared_ptr<EventProgressPublisher> mPub;
};

#endif