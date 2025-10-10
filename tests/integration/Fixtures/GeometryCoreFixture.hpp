#ifndef GeometryCoreFixture_hpp
#define GeometryCoreFixture_hpp

#include "OcafKernelFixutre.hpp"
#include "GeometryCore.hpp"

class GeometryCoreFixture : public OcafKernelFixture {
    protected:
    void SetUp () {
        geometryCore = std::make_unique<GeometryCore>(
            *kernel
        );
    }
    std::unique_ptr<GeometryCore> geometryCore;
};

#endif