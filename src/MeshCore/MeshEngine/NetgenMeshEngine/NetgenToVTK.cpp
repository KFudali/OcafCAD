#include "NetgenToVTK.hpp"

#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkHexahedron.h>
#include <vtkLogger.h>
#include <vtkPoints.h>
#include <vtkQuad.h>
#include <vtkTetra.h>
#include <vtkTriangle.h>
#include <vtkUnsignedCharArray.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellArray.h>
#include <vtkUnsignedCharArray.h>
#include <numeric>
#include <execution>
#include <meshing.hpp>


#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <algorithm> 
#include <vtkDoubleArray.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <cstring>
#include <numeric>
#include <execution>

vtkSmartPointer<vtkPoints> wrapPoints(const netgen::Mesh& aSource) {
    auto nPoints = aSource.GetNP();
    const auto& points = aSource.Points();
    const double* raw = &points[0][0];
    
	auto array = vtkSmartPointer<vtkDoubleArray>::New();
    array->SetNumberOfComponents(3);
    array->SetArray(const_cast<double*>(raw), nPoints*3, 1);

    auto vtkPts = vtkSmartPointer<vtkPoints>::New();
    vtkPts->SetData(array);

    return vtkPts;
}

vtkSmartPointer<vtkPoints> copyPoints(const netgen::Mesh& mesh)
{
    auto nPoints = mesh.GetNP();
    const auto& points = mesh.Points();

    auto array = vtkSmartPointer<vtkDoubleArray>::New();
    array->SetNumberOfComponents(3);
    array->SetNumberOfTuples(nPoints);

    double* vtkBuf = array->GetPointer(0);
    std::memcpy(vtkBuf, &points[0][0], nPoints * 3 * sizeof(double));

    auto vtkPts = vtkSmartPointer<vtkPoints>::New();
    vtkPts->SetData(array);

    return vtkPts;
}

#include <numeric>

template <typename ElemContainer>
std::vector<vtkIdType> computeOffsets(const ElemContainer& elems)
{
    size_t n = elems.size();
    std::vector<vtkIdType> offsets(n);

    std::exclusive_scan(
        std::execution::par,
        elems.begin(),
        elems.end(),
        offsets.begin(),
        vtkIdType(0),
        [](vtkIdType sum, const auto& e){ return sum + 1 + e.GetNP(); }
    );

    return offsets;
}
template <typename ElemContainer>
size_t computeTotalConnectivityFromOffsets(
	const std::vector<vtkIdType>& offsets, const ElemContainer& elems
)
{
    size_t n = elems.size();
    if (n == 0) return 0;
    return offsets.back() + 1 + elems.back().GetNP();
}

vtkSmartPointer<vtkCellArray> copySurfaceConnectivity(const netgen::Mesh& aSource) {
    const auto& sourceElems = aSource.SurfaceElements();
    size_t nElems = sourceElems.Size();
    if (nElems == 0) return vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkIdTypeArray> offsetsVTK = vtkSmartPointer<vtkIdTypeArray>::New();
    offsetsVTK->SetNumberOfValues(nElems);
    
	vtkIdType totalConn = 0;
    for (size_t i = 0; i < nElems; ++i) {
        const auto& elem = sourceElems[i];
        totalConn += 1 + elem.GetNP();
        offsetsVTK->SetValue(i, totalConn);
    }

    vtkSmartPointer<vtkIdTypeArray> connVTK = vtkSmartPointer<vtkIdTypeArray>::New();
    connVTK->SetNumberOfValues(totalConn);

    for (size_t i = 0; i < nElems; ++i) {
        const auto& elem = sourceElems[i];
        vtkIdType offset = offsetsVTK->GetValue(i) - (1 + elem.GetNP());
        connVTK->SetValue(offset, static_cast<vtkIdType>(elem.GetNP()));
        for (size_t j = 0; j < elem.GetNP(); ++j) {
            connVTK->SetValue(offset + 1 + j, static_cast<vtkIdType>(elem.PNum(j)));
        }
    }

    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    cells->SetData(offsetsVTK, connVTK);

    return cells;
}

inline unsigned char MapCellType(int typ) {
    switch (typ) {
        case netgen::TET: return VTK_TETRA;
        case netgen::HEX: return VTK_HEXAHEDRON;
        case netgen::PRISM: return VTK_WEDGE;
        case netgen::PYRAMID: return VTK_PYRAMID;
        default: return VTK_EMPTY_CELL;
    }
}

vtkSmartPointer<vtkUnstructuredGrid> copyVolumeConnectivity(
    const netgen::Mesh& mesh, vtkSmartPointer<vtkPoints> points
){
    const auto& elems = mesh.VolumeElements();
    size_t nElems = mesh.GetNE();
    if (nElems == 0) return vtkSmartPointer<vtkUnstructuredGrid>::New();

    vtkSmartPointer<vtkIdTypeArray> offsetsVTK = vtkSmartPointer<vtkIdTypeArray>::New();
    offsetsVTK->SetNumberOfValues(nElems);

    vtkIdType totalConn = 0;
    for (size_t i = 0; i < nElems; ++i) {
        const auto& elem = elems[i];
        totalConn += 1 + elem.GetNP();
        offsetsVTK->SetValue(i, totalConn);
    }

    vtkSmartPointer<vtkIdTypeArray> connVTK = vtkSmartPointer<vtkIdTypeArray>::New();
    connVTK->SetNumberOfValues(totalConn);

    vtkSmartPointer<vtkUnsignedCharArray> cellTypes = vtkSmartPointer<vtkUnsignedCharArray>::New();
    cellTypes->SetNumberOfValues(nElems);

    for (size_t i = 0; i < nElems; ++i) {
        const auto& elem = elems[i];

        vtkIdType offset = offsetsVTK->GetValue(i) - (1 + elem.GetNP());
        connVTK->SetValue(offset, static_cast<vtkIdType>(elem.GetNP()));
        for (size_t j = 0; j < elem.GetNP(); ++j) {
            connVTK->SetValue(offset + 1 + j, static_cast<vtkIdType>(elem.PNum(j)));
        }

        cellTypes->SetValue(i, MapCellType(elem.GetType()));
    }

    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    cells->SetData(offsetsVTK, connVTK);

    vtkSmartPointer<vtkUnstructuredGrid> uGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    uGrid->SetPoints(points);
    uGrid->SetCells(cellTypes, cells);

    return uGrid;
}

bool NetgenToVTK::transfer(const netgen::Mesh& aSource, Mesh& aDest) {
	auto points = copyPoints(aSource);
	auto surfaceCells = copySurfaceConnectivity(aSource);
	auto volumeGrid = copyVolumeConnectivity(aSource, points);
	return true;
}