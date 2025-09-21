#include "GeometryCore.hpp"

GeometryCore::GeometryCore() : mOcafKernel(std::make_unique<OcafKernel>()) {};

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
