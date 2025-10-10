#include "GeometryCore.hpp"

GeometryCore::GeometryCore(
    OcafKernel& aOcafKernel
) : mDocumentGeometry(aOcafKernel.doc().geometry()),
    mView(std::make_unique<GeometryView>(aOcafKernel.doc().geometry())),
    mEvents(std::make_unique<GeometryEventSource>(aOcafKernel.events())) {}

void GeometryCore::import(
    AbstractImporter& aImporter,
    AbstractProgressPublisher& aPublisher
) {
    aImporter.importIntoDoc(mDocumentGeometry, aPublisher);
}

void GeometryCore::import(
    AbstractImporter& aImporter
) {
    auto publisher = IdleProgressPublisher();
    import(aImporter, publisher);
}
