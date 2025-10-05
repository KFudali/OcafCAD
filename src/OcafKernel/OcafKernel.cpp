#include "OcafKernel.hpp"
#include "SignalMessageBus.hpp"

OcafKernel::OcafKernel() {
    auto app = XCAFApp_Application::GetApplication();
    mDocument = std::make_unique<MainDocument>(app);
    mCommandStack = std::make_unique<CommandStack>(mDocument->data());
    mMessageBus = std::make_unique<SignalMessageBus>();

    mDeltaObservers = std::make_unique<DeltaObservers>(*mMessageBus);
    mCommandStack->appendDeltaObserver(mDeltaObservers->geometry());    

}