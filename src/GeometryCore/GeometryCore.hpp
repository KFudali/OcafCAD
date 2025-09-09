#ifndef GeometryCore_hpp
#define GeometryCore_hpp

#include <memory>
#include "OcafKernel.hpp"

class GeometryCore {
    public:
    GeometryCore();

    private:
    std::unique_ptr<OcafKernel> mOcafKernel;
};

#endif