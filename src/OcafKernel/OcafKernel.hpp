#ifndef OcafKernel_hpp
#define OcafKernel_hpp

#include <memory>

#include "PartDocument.hpp"
#include "AbstractDocCommandStack.hpp"

#include "AbstractMessageBus.hpp"
#include "MessageSubscriber.hpp"
#include "AbstractOcafKernelPublisher.hpp"
#include "AbstractDeltaObserver.hpp"

class OcafKernel{
    public:
    OcafKernel();
   
    PartDocument& partDocument(){ return *mPartDocument; };
    AbstractDocCommandStack& commands() {return *mCommandStack; };
    MessageSubscriber& events() {return *mSubscriber;};
    
    private:
    std::unique_ptr<PartDocument> mPartDocument;
    std::unique_ptr<AbstractDocCommandStack> mCommandStack;

    std::unique_ptr<AbstractMessageBus> mInternalMessageBus;
    std::unique_ptr<MessageSubscriber> mSubscriber;
    std::unique_ptr<AbstractOcafKernelPublisher> mPublisher;
    std::unique_ptr<AbstractDeltaObserver> mDeltaObserver;

};

#endif