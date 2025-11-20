#ifndef VolumeExtraction_hpp
#define VolumeExtraction_hpp

#include <meshing.hpp>
#include <occgeom.hpp>
#include <memory>
#include <vector>

#include "MeshExtractionUtils.hpp"
#include "VolumeConnectivity.hpp"
#include "Points.hpp"

namespace VolumeExtraction{

    VolumeConnectivity extractVolumeConnectivity(
        const ElemContainer& elems,
        const std::unordered_map<int, DomainId>& surfaceDomainMap,
        vtkSmartPointer<vtkIdTypeArray> offsets,
        std::execution::sequenced_policy exec = std::execution::seq
    )

};

#endif