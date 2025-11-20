#ifndef VolumeMesh_hpp
#define VolumeMesh_hpp

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellData.h>
#include <vtkUnsignedCharArray.h>
#include <string>

#include "VolumeConnectivity.hpp"

class VolumeMesh {
public:
    static constexpr const char* shapeIdsArrayName  = "shapeIds";
    static constexpr const char* domainIdsArrayName = "domainIds";

    VolumeMesh(
        vtkSmartPointer<vtkPoints> points,
        const VolumeConnectivity& conn
    )
    {
        mGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();

        mGrid->SetPoints(points);

        conn.shapeIds->SetName(shapeIdsArrayName);
        conn.domainIds->SetName(domainIdsArrayName);

        mGrid->SetCells(conn.cellTypes, conn.cells);

        mGrid->GetCellData()->AddArray(conn.shapeIds);
        mGrid->GetCellData()->AddArray(conn.domainIds);
    }
    
    vtkSmartPointer<vtkUnstructuredGrid> data() const {
        return mGrid;
    }

private:
    vtkSmartPointer<vtkUnstructuredGrid> mGrid;
};

#endif // VolumeMesh_hpp