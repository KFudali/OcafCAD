#ifndef Mesh_hpp
#define Mesh_hpp

#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>

class Mesh {
public:
    Mesh() = default;

    void setBoundaryMesh(vtkSmartPointer<vtkPolyData> aBoundaryMesh) {
        mBoundaryMesh = aBoundaryMesh;
    }
    void setInternalMesh(vtkSmartPointer<vtkUnstructuredGrid> aInternalMesh) {
        mInternalMesh = aInternalMesh;
    }

    inline vtkSmartPointer<vtkPolyData> boundaryMesh() const {
        return mBoundaryMesh;
    }
    inline vtkSmartPointer<vtkUnstructuredGrid> internalMesh() const {
        return mInternalMesh;
    }

    inline bool hasBoundaryMesh() const { return static_cast<bool>(mBoundaryMesh); }
    inline bool hasInternalMesh() const { return static_cast<bool>(mInternalMesh); }

private:
    vtkSmartPointer<vtkUnstructuredGrid> mInternalMesh;
    vtkSmartPointer<vtkPolyData> mBoundaryMesh;
};

#endif
