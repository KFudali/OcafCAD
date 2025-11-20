#ifndef SurfaceConnectivity_hpp
#define SurfaceConnectivity_hpp

#include "Connectivity.hpp"

struct SurfaceConnectivity : public Connectivity {
    SurfaceConnectivity() = default;
    SurfaceConnectivity(
        vtkSmartPointer<vtkCellArray> cells,
        vtkSmartPointer<vtkIdTypeArray> shapeIds,
        vtkSmartPointer<vtkIdTypeArray> domainIds
    ) : Connectivity(cells, shapeIds, domainIds) {};
};

#endif