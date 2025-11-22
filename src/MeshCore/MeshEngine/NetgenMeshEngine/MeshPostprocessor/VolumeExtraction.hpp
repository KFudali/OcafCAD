#ifndef VolumeExtraction_hpp
#define VolumeExtraction_hpp

#include <meshing.hpp>
#include <occgeom.hpp>
#include <memory>
#include <vector>

#include "MeshExtractionUtils.hpp"
#include "VolumeConnectivity.hpp"
#include "NetgenElemContainers.hpp"

namespace VolumeExtraction{
    VolumeConnectivity extractVolumeConn(
        const Elem3DContainer& elems,
        const std::unordered_map<int, DomainId>& volumeDomainMap,
        vtkSmartPointer<vtkIdTypeArray> offsets,
        std::execution::sequenced_policy exec = std::execution::seq
    );
};

#endif