#ifndef OcafKernelFixture_hpp
#define OcafKernelFixture_hpp

#include <gmock/gmock.h>
#include "OcafKernel.hpp"

class OcafKernelFixture : public ::testing::Test {
    protected:
    void SetUp () {
        kernel = std::make_unique<OcafKernel>();
    }
    std::unique_ptr<OcafKernel> kernel;
};

#endif