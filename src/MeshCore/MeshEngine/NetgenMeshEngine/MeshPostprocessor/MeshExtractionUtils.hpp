#ifndef MeshExtractionUtils_hpp
#define MeshExtractionUtils_hpp


#include <occgeom.hpp>
#include <meshing.hpp>

#include <vtkType.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>

#include <memory>
#include <vector>
#include <numeric>
#include <execution>
#include <unordered_map>

#include "DomainId.hpp"
#include "SurfaceConnectivity.hpp"
#include "NetgenElemContainers.hpp"

namespace MeshExtractionUtils {

    vtkSmartPointer<vtkPoints> extractPoints(std::shared_ptr<netgen::Mesh> mesh);

    vtkSmartPointer<vtkIdTypeArray> computeOffsets(
        const Elem2DContainer& elems,
        std::execution::sequenced_policy exec = std::execution::seq
    );

    vtkSmartPointer<vtkIdTypeArray> computeConn(
        const Elem2DContainer& elems,
        vtkSmartPointer<vtkIdTypeArray> offsets,
        std::execution::sequenced_policy exec = std::execution::seq
    );
};

#endif