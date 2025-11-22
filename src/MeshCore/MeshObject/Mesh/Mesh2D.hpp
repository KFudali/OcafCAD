#ifndef Mesh2D_hpp
#define Mesh2D_hpp

#include "SurfaceConnectivity.hpp"
#include <vtkPoints.h>
#include <vtkSmartPointer.h>

class Mesh2D{
    Mesh2D(
        vtkSmartPointer<vtkPoints> aPoints,
        const SurfaceConnectivity& aSurfConn,
    ) : mPoints(aPoints), mSurfConn(aSurfConn) {}

    vtkSmartPointer<vtkPoints> mPoints; 
    const SurfaceConnectivity mSurfConn;
};

#endif