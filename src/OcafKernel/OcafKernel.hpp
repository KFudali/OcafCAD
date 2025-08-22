#ifndef OcafKernel_hpp
#define OcafKernel_hpp

#include <memory>

class OcafKernel{
    public:
    OcafKernel(std::shared_ptr<AbstractMessageBus> aMessageBus);
    
    std::unique_ptr<PartDocument> partDocument();
   
    std::unique_ptr<MessageSubscriber> deltaEvents();
    std::unique_ptr<CommandStack> commands();
    
    private:
    std::unique_ptr<PartDocument> mPartDocument;
    std::unique_ptr<DeltaObserver> mDeltaObserver;
    std::unique_ptr<CommandStack> mCommandStack;
};

#endif