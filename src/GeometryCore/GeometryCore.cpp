#include "GeometryCore.hpp"

GeometryCore::GeometryCore() : mOcafKernel(std::make_unique<OcafKernel>()) {};

void GeometryCore::import(AbstractImporter& aImporter) {
    // aImporter.importIntoDoc(mOcafKernel->partDocument())
}
