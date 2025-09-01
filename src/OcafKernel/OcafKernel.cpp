#include "OcafKernel.hpp"

#include <XCAFApp_Application.hxx>
#include <XmlXCAFDrivers.hxx>
#include "OcafKernelPublisherAdapter.hpp"

OcafKernel::OcafKernel() {
    auto app = XCAFApp_Application::GetApplication();
    XmlXCAFDrivers::DefineFormat(app);
    mPartDocument = std::make_unique<PartDocument>(app);
    mCommandStack = std::make_unique<CommandStack>(mPartDocument->data());
    mPublisher = std::make_unique<OcafKernelSignalPublisher>();
}

OcafKernelConnections OcafKernel::connectObserver(
    AbstractOcafKernelObserver& aObserver
){
    return OcafKernelPublisherAdapter::connectOcafObserver(
        aObserver, *mPublisher
    );
}
