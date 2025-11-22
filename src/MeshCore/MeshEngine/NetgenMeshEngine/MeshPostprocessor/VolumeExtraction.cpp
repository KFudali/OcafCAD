#include "VolumeExtraction.hpp"
#include "MeshExtractionUtils.hpp"

#include <vtkSmartPointer.h>
#include <vtkType.h>
#include <vtkIdTypeArray.h>
#include <vtkUnsignedCharArray.h>

#include <vtkCellType.h>
#include <array>
#include <stdexcept>

using ELEMENT_TYPE = netgen::ELEMENT_TYPE;
constexpr std::array<std::pair<ELEMENT_TYPE, unsigned char>, 18> ElementToVTKMap {{
    { ELEMENT_TYPE::SEGMENT,      VTK_LINE },
    { ELEMENT_TYPE::SEGMENT3,     VTK_QUADRATIC_EDGE },

    { ELEMENT_TYPE::TRIG,         VTK_TRIANGLE },
    { ELEMENT_TYPE::TRIG6,        VTK_QUADRATIC_TRIANGLE },

    { ELEMENT_TYPE::QUAD,         VTK_QUAD },
    { ELEMENT_TYPE::QUAD6,        VTK_QUADRATIC_QUAD },
    { ELEMENT_TYPE::QUAD8,        VTK_QUADRATIC_QUAD },

    { ELEMENT_TYPE::TET,          VTK_TETRA },
    { ELEMENT_TYPE::TET10,        VTK_QUADRATIC_TETRA },

    { ELEMENT_TYPE::PYRAMID,      VTK_PYRAMID },
    { ELEMENT_TYPE::PYRAMID13,    VTK_QUADRATIC_PYRAMID },

    { ELEMENT_TYPE::PRISM,        VTK_WEDGE },
    { ELEMENT_TYPE::PRISM12,      VTK_QUADRATIC_WEDGE },
    { ELEMENT_TYPE::PRISM15,      VTK_QUADRATIC_WEDGE },

    { ELEMENT_TYPE::HEX,          VTK_HEXAHEDRON },
    { ELEMENT_TYPE::HEX20,        VTK_QUADRATIC_HEXAHEDRON },

    { ELEMENT_TYPE::HEX7,         VTK_POLYHEDRON }  // fallback
}};
constexpr unsigned char NetgenToVTKCellType(ELEMENT_TYPE t)
{
    for (auto [key, value] : ElementToVTKMap) {
        if (key == t)
            return value;
    }
    throw std::runtime_error("Unknown ELEMENT_TYPE -> VTK mapping");
}

VolumeConnectivity VolumeExtraction::extractVolumeConn(
    const Elem3DContainer& elems,
    const std::unordered_map<int, DomainId>& volumeDomainMap,
    vtkSmartPointer<vtkIdTypeArray> offsets,
    std::execution::sequenced_policy exec
) {
    const size_t n = std::distance(elems.begin(), elems.end());
    auto conn = vtkSmartPointer<vtkIdTypeArray>::New();
    auto elemPointCountSum = offsets->GetValue(offsets->GetSize() - 1);
    conn->SetNumberOfValues(elemPointCountSum);
    vtkIdType* connPtr = conn->GetPointer(0);
    
    auto shapeIds = vtkSmartPointer<vtkIdTypeArray>::New();
    auto domainIds = vtkSmartPointer<vtkIdTypeArray>::New();
    auto elemTypes = vtkSmartPointer<vtkUnsignedCharArray>::New();

    shapeIds->SetNumberOfValues(n);
    domainIds->SetNumberOfValues(n);
    elemTypes->SetNumberOfValues(n);

    auto indices = std::views::iota(static_cast<size_t>(0), n);
    std::for_each(exec, indices.begin(), indices.end(), [&](vtkIdType ei) {
        const vtkIdType start = offsets->GetValue(ei);
        const vtkIdType end   = offsets->GetValue(ei + 1);
        const vtkIdType npts  = end - start;
        const auto& elem = elems[ei];
        ELEMENT_TYPE t = elems[ei].GetType();
        unsigned char vtkType = NetgenToVTKCellType(t);
        elemTypes->SetValue(ei, vtkType);
        auto surfNum = elem.GetIndex();
        shapeIds->SetValue(ei, surfNum);
        auto it = volumeDomainMap.find(surfNum);
        if (it != volumeDomainMap.end()) {
            domainIds->SetValue(ei, it->second.value());
        } else {
            domainIds->SetValue(ei, surfNum);
        }
        const netgen::PointIndex* p = elems[ei].PNums().Data();
        std::copy(p, p + npts, connPtr + start);
    });
    auto cells = vtkSmartPointer<vtkCellArray>::New();
    cells->SetData(offsets, conn);

    return VolumeConnectivity(cells, shapeIds, domainIds, elemTypes);
}