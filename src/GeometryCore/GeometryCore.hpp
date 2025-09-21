#ifndef GeometryCore_hpp
#define GeometryCore_hpp

#include <memory>
#include "AbstractImporter.hpp"
#include "STEPImporter.hpp"
#include "OcafKernel.hpp"

class GeometryCore {
    public:
    GeometryCore();

    void import(AbstractImporter& aImporter, AbstractProgressPublisher& aPublisher);
    void import(AbstractImporter& aImporter);
   
    void clear();

    private:
    std::unique_ptr<OcafKernel> mOcafKernel;
};

#endif