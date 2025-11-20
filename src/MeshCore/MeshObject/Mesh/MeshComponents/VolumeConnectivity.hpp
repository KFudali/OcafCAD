#ifndef VolumeConnectivity_hpp
#define VolumeConnectivity_hpp

#include "Connectivity.hpp"
#include <vtkUnsignedCharArray.h>

struct VolumeConnectivity : public Connectivity {
    VolumeConnectivity() = default;

    VolumeConnectivity(
        vtkSmartPointer<vtkCellArray> cells,
        vtkSmartPointer<vtkIdTypeArray> shapeIds,
        vtkSmartPointer<vtkIdTypeArray> domainIds,
        vtkSmartPointer<vtkUnsignedCharArray> cellTypes
    ) : Connectivity(cells, shapeIds, domainIds) {}

    vtkSmartPointer<vtkUnsignedCharArray> cellTypes = vtkSmartPointer<vtkUnsignedCharArray>::New();
};

#endif
