#ifndef OcafKernel_hpp
#define OcafKernel_hpp

#include <memory>

#include "PartDocument.hpp"
#include "CommandStack.hpp"
#include "OcafKernelSignalPublisher.hpp"
#include "AbstractOcafKernelObserver.hpp"
#include "OcafKernelConnections.hpp"

class OcafKernel{
    public:
    OcafKernel();
    
    PartDocument& partDocument(){ return *mPartDocument; };
    CommandStack& commands() {return *mCommandStack; };
   
    OcafKernelConnections connectObserver(
        AbstractOcafKernelObserver& aObserver
    );
    
    private:
    std::unique_ptr<PartDocument> mPartDocument;
    std::unique_ptr<OcafKernelSignalPublisher> mPublisher;
    std::unique_ptr<CommandStack> mCommandStack;
};

#endif