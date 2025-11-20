#ifndef Mesh3D_hpp
#define Mesh3D_hpp

#include "SurfaceConnectivity.hpp"
#include "VolumeConnectivity.hpp"



class Mesh3D {
    Mesh3D(
        const Points& aPoints,
        const SurfaceConnectivity& aSurfConn,
        const VolumeConnectivity& aVolumeConn
    ) {}
   
    vtkSmartPointer<vtkUnstructuredGrid> mGrid;
};

#endif