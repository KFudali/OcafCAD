#ifndef Mesh3D_hpp
#define Mesh3D_hpp

#include "SurfaceConnectivity.hpp"
#include "VolumeConnectivity.hpp"

#include <vtkPoints.h>
#include <vtkSmartPointer.h>

class Mesh3D {
    Mesh3D(
        vtkSmartPointer<vtkPoints> aPoints,
        const SurfaceConnectivity& aSurfConn,
        const VolumeConnectivity& aVolumeConn
    ) {}
   
    vtkSmartPointer<vtkPoints> mPoints;
    SurfaceConnectivity mSurfConn;
    VolumeConnectivity mVolumeConn;
};

#endif