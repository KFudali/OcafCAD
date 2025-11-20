#ifndef SurfaceMesh_hpp
#define SurfaceMesh_hpp

#include <vtkSmartPointer.h>
#include <vtkCellData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <string>

#include "SurfaceConnectivity.hpp"

class SurfaceMesh {
public:
    static constexpr const char* faceIdsArrayName   = "faceIds";
    static constexpr const char* domainIdsArrayName = "domainIds";

    SurfaceMesh(
        vtkSmartPointer<vtkPoints> points,
        const SurfaceConnectivity& conn
    ) 
    {
        mPolyData = vtkSmartPointer<vtkPolyData>::New();

        mPolyData->SetPoints(points);
        mPolyData->SetPolys(conn.cells);

        conn.shapeIds->SetName(faceIdsArrayName);
        conn.domainIds->SetName(domainIdsArrayName);

        mPolyData->GetCellData()->AddArray(conn.shapeIds);
        mPolyData->GetCellData()->AddArray(conn.domainIds);
    }
    
    inline vtkSmartPointer<vtkPolyData> data() const { return mPolyData; }
    
private:
    vtkSmartPointer<vtkPolyData> mPolyData;
};

#endif // SurfaceMesh_hpp
