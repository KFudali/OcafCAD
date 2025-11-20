#include "MeshExtractionUtils.hpp"

#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include <vtkIdTypeArray.h>

vtkSmartPointer<vtkPoints> MeshExtractionUtils::extractPoints(
    std::shared_ptr<netgen::Mesh> mesh
) {
    if (!mesh) return nullptr;

    auto nPoints = mesh->GetNP();
    const auto& pts = mesh->Points();

    auto array = vtkSmartPointer<vtkDoubleArray>::New();
    array->SetNumberOfComponents(3);
    array->SetNumberOfTuples(nPoints);

    double* vtkBuf = array->GetPointer(0);

    for (size_t i = 0; i < nPoints; ++i) {
        const auto& mp = pts[netgen::PointIndex(i + 1)];
        const double* src = mp;
        std::memcpy(&vtkBuf[3 * i], src, 3 * sizeof(double));
    }

    auto vtkPts = vtkSmartPointer<vtkPoints>::New();
    vtkPts->SetData(array);
    return vtkPts;
}

vtkSmartPointer<vtkIdTypeArray> MeshExtractionUtils::computeOffsets(
    const ElemContainer& elems,
    std::execution::sequenced_policy exec
) {
    const size_t n = std::distance(elems.begin(), elems.end());
    auto offsets = vtkSmartPointer<vtkIdTypeArray>::New();
    if (n == 0){
        offsets->SetNumberOfValues(1);
        offsets->SetValue(0, 0);
        return offsets;
    }
    offsets->SetNumberOfValues(static_cast<vtkIdType>(n + 1));

    std::exclusive_scan(
        exec,
        elems.begin(),
        elems.end(),
        offsets->Begin(),
        vtkIdType(0),
        [](vtkIdType sum, const auto& e){ return sum + e.GetNP(); }
    );
    auto lastOffset = offsets->GetValue(n - 1) + static_cast<vtkIdType>(elems[n - 1].GetNP());
    offsets->SetValue(n, lastOffset);
    return offsets;
}

vtkSmartPointer<vtkIdTypeArray> MeshExtractionUtils::computeConn(
    const ElemContainer& elems,
    vtkSmartPointer<vtkIdTypeArray> offsets,
    std::execution::sequenced_policy exec
) {
    const size_t n = std::distance(elems.begin(), elems.end());
    auto conn = vtkSmartPointer<vtkIdTypeArray>::New();
    auto elemPointCountSum = offsets->GetValue(offsets->GetSize() - 1);
    conn->SetNumberOfValues(elemPointCountSum);

    vtkIdType* connPtr = conn->GetPointer(0);

    auto indices = std::views::iota(static_cast<size_t>(0), n);
    std::for_each(exec, indices.begin(), indices.end(), [&](vtkIdType ei) {
        vtkIdType start = offsets->GetValue(ei);
        vtkIdType end   = offsets->GetValue(ei + 1);
        vtkIdType npts  = end - start;
        const netgen::PointIndex* p = elems[ei].PNums().Data();
        std::copy(p, p + npts, connPtr + start);
    });
    return conn;
}