#ifndef SurfaceExtraction_hpp
#define SurfaceExtraction_hpp


#include <meshing.hpp>
#include <occgeom.hpp>
#include <memory>
#include <vector>

#include "MeshExtractionUtils.hpp"
#include "SurfaceConnectivity.hpp"
#include "Points.hpp"

namespace SurfaceExtraction {
    using ElemContainer = ngcore::Array<netgen::Element2d, netgen::SurfaceElementIndex>;
    SurfaceConnectivity extractSurfaceConn(
        const ElemContainer& elems,
        const std::unordered_map<int, DomainId>& surfaceDomainMap,
        vtkSmartPointer<vtkIdTypeArray> offsets,
        std::execution::sequenced_policy exec = std::execution::seq
    );
}


#endif