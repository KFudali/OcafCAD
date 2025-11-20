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


namespace MeshExtractionUtils {


    using ElemContainer = ngcore::Array<netgen::Element2d, netgen::SurfaceElementIndex>;
    vtkSmartPointer<vtkIdTypeArray> computeOffsets(
        const ElemContainer& elems,
        std::execution::sequenced_policy exec = std::execution::seq
    );

    vtkSmartPointer<vtkIdTypeArray> computeConn(
        const ElemContainer& elems,
        vtkSmartPointer<vtkIdTypeArray> offsets,
        std::execution::sequenced_policy exec = std::execution::seq
    );
    vtkSmartPointer<vtkPoints> extractPoints(std::shared_ptr<netgen::Mesh> mesh);

};

#endif