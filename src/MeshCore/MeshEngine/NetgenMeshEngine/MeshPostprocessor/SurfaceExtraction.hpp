#ifndef SurfaceExtraction_hpp
#define SurfaceExtraction_hpp


#include <meshing.hpp>
#include <occgeom.hpp>
#include <memory>
#include <vector>

#include "MeshExtractionUtils.hpp"
#include "SurfaceConnectivity.hpp"
#include "NetgenElemContainers.hpp"
#include "Points.hpp"

namespace SurfaceExtraction {
    SurfaceConnectivity extractSurfaceConn(
        const Elem2DContainer& elems,
        const std::unordered_map<int, DomainId>& surfaceDomainMap,
        vtkSmartPointer<vtkIdTypeArray> offsets,
        std::execution::sequenced_policy exec = std::execution::seq
    );
}


#endif