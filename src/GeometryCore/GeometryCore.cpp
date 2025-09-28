#include "GeometryCore.hpp"

GeometryCore::GeometryCore() 
  : mOcafKernel(std::make_unique<OcafKernel>()),
    mView(std::make_unique<GeometryView>(mOcafKernel->partDocument())),
    mEvents(std::make_unique<GeometryEventSource>(mOcafKernel->events())) {}

void GeometryCore::import(
    AbstractImporter& aImporter,
    AbstractProgressPublisher& aPublisher
) {
    aImporter.importIntoDoc(mOcafKernel->partDocument(), aPublisher);
}

void GeometryCore::import(
    AbstractImporter& aImporter
) {
    auto publisher = IdleProgressPublisher();
    aImporter.importIntoDoc(mOcafKernel->partDocument(), publisher);
}
