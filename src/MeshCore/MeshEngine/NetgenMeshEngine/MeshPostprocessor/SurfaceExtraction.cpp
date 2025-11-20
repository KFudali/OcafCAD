#include "SurfaceExtraction.hpp"
#include "MeshExtractionUtils.hpp"

#include <vtkSmartPointer.h>
#include <vtkType.h>
#include <vtkIdTypeArray.h>
#include <vtkPolyData.h>

SurfaceConnectivity SurfaceExtraction::extractSurfaceConn(
    const ElemContainer& elems,
    const std::unordered_map<int, DomainId>& surfaceDomainMap,
    vtkSmartPointer<vtkIdTypeArray> offsets,
    std::execution::sequenced_policy exec
) {
    const size_t n = std::distance(elems.begin(), elems.end());
    auto conn = vtkSmartPointer<vtkIdTypeArray>::New();
    auto elemPointCountSum = offsets->GetValue(offsets->GetSize() - 1);
    conn->SetNumberOfValues(elemPointCountSum);

    vtkIdType* connPtr = conn->GetPointer(0);
    
    auto surfIds = vtkSmartPointer<vtkIdTypeArray>::New();
    auto domainIds = vtkSmartPointer<vtkIdTypeArray>::New();
    surfIds->SetNumberOfValues(n);
    domainIds->SetNumberOfValues(n);
    
    auto indices = std::views::iota(static_cast<size_t>(0), n);
    std::for_each(exec, indices.begin(), indices.end(), [&](vtkIdType ei) {
        const vtkIdType start = offsets->GetValue(ei);
        const vtkIdType end   = offsets->GetValue(ei + 1);
        const vtkIdType npts  = end - start;
        const auto& elem = elems[ei];
        auto surfNum = elem.GetIndex();
        surfIds->SetValue(ei, surfNum);
        auto it = surfaceDomainMap.find(surfNum);
        if (it != surfaceDomainMap.end()) {
            domainIds->SetValue(ei, it->second.value());
        } else {
            domainIds->SetValue(ei, surfNum);
        }
        const netgen::PointIndex* p = elems[ei].PNums().Data();
        std::copy(p, p + npts, connPtr + start);
    });
    auto cells = vtkSmartPointer<vtkCellArray>::New();
    cells->SetData(offsets, conn);

    return SurfaceConnectivity(cells, surfIds, domainIds);
}
