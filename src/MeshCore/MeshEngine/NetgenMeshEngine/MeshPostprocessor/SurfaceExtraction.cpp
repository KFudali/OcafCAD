#include "SurfaceExtraction.hpp"
#include "MeshExtractionUtils.hpp"

#include <vtkSmartPointer.h>
#include <vtkType.h>
#include <vtkIdTypeArray.h>
#include <vtkPolyData.h>

SurfaceConnectivity SurfaceExtraction::extractSurfaceConnectivity(
    std::shared_ptr<netgen::Mesh> mesh
) {
    // const auto& sourceElems = mesh->SurfaceElements();
    // using ElemContainer = ngcore::Array<netgen::Element2d, netgen::SurfaceElementIndex>;
    // const auto offsets = MeshExtractionUtils::computeOffsets<ElemContainer>(
    //     sourceElems
    // );
    // const auto conn = MeshExtractionUtils::computeConnectivity<ElemContainer>(
    //     sourceElems, offsets
    // );
    // const auto points = MeshExtractionUtils::extractPoints(mesh);


    // vtkSmartPointer<vtkIdTypeArray> vtkConn = vtkSmartPointer<vtkIdTypeArray>::New();
    // vtkIdType* rawConn = new vtkIdType[conn.size()];
    // std::memcpy(rawConn, conn.data(), conn.size() * sizeof(vtkIdType));
    // vtkConn->SetArray(rawConn, static_cast<vtkIdType>(conn.size()), 1);

    // vtkSmartPointer<vtkIdTypeArray> vtkOffsets = vtkSmartPointer<vtkIdTypeArray>::New();
    // vtkIdType* rawOffsets = new vtkIdType[offsets.size()];
    // std::memcpy(rawOffsets, offsets.data(), offsets.size() * sizeof(vtkIdType));
    // vtkOffsets->SetArray(rawOffsets, static_cast<vtkIdType>(offsets.size()), 1);

    // vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    // cells->SetData(vtkOffsets, vtkConn);
    // vtkSmartPointer<vtkIdTypeArray> shapeIds = vtkSmartPointer<vtkIdTypeArray>::New();
    // vtkSmartPointer<vtkIdTypeArray> domainIds = vtkSmartPointer<vtkIdTypeArray>::New();
    return SurfaceConnectivity();
}