#include "OcafKernel.hpp"

#include <XCAFApp_Application.hxx>
#include <XmlXCAFDrivers.hxx>

#include "SignalMessageBus.hpp"
#include "SignalOcafKernelPublisher.hpp"
#include "PublisherDeltaObserver.hpp"
#include "DocCommandStack.hpp"

OcafKernel::OcafKernel() {
    auto app = XCAFApp_Application::GetApplication();
    XmlXCAFDrivers::DefineFormat(app);
    mPartDocument = std::make_unique<PartDocument>(app);
    mCommandStack = std::make_unique<DocCommandStack>(mPartDocument->data());
    mInternalMessageBus = std::make_unique<SignalMessageBus>();
    mSubscriber = std::make_unique<MessageSubscriber>(*mInternalMessageBus);
    mPublisher = std::make_unique<SignalOcafKernelPublisher>(*mInternalMessageBus);
    mDeltaObserver = std::make_unique<PublisherDeltaObserver>(*mPublisher);

    mCommandStack->appendDeltaObserver(mDeltaObserver.get());
}