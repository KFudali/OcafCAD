#ifndef OcafKernel_hpp
#define OcafKernel_hpp

#include "MainDocument.hpp"
#include "CommandStack.hpp"
#include "AbstractMessageBus.hpp"
#include "DeltaObservers.hpp"

class OcafKernel {
    public:
    OcafKernel();

    inline MainDocument& doc() {return *mDocument;}
    inline CommandStack& commands() {return *mCommandStack;}
    inline AbstractMessageBus& events() {return *mMessageBus;}

    private:
    std::unique_ptr<AbstractMessageBus> mMessageBus;
    
    std::unique_ptr<MainDocument> mDocument;
    std::unique_ptr<CommandStack> mCommandStack;

    std::unique_ptr<DeltaObservers> mDeltaObservers; 

};

#endif