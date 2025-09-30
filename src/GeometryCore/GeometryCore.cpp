#include "GeometryCore.hpp"

GeometryCore::GeometryCore() 
  : mOcafKernel(std::make_unique<OcafKernel>()),
    mView(std::make_unique<GeometryView>(mOcafKernel->partDocument())),
    mEvents(std::make_unique<GeometryEventSource>(mOcafKernel->events())) {}

void GeometryCore::import(
    AbstractImporter& aImporter,
    AbstractProgressPublisher& aPublisher
) {
    mOcafKernel->commands().openCommand();
    aImporter.importIntoDoc(mOcafKernel->partDocument(), aPublisher);
    mOcafKernel->commands().commitCommand();
}

void GeometryCore::import(
    AbstractImporter& aImporter
) {
    auto publisher = IdleProgressPublisher();
    import(aImporter, publisher);
}
