#ifndef Mesh2D_hpp
#define Mesh2D_hpp

#include "SurfaceConnectivity.hpp"

struct Mesh2D{
    Mesh2D(
        const Points& aPoints,
        const SurfaceConnectivity& aSurfConn,
    ) : surface(surface), volume(volume) {}
    
    SurfaceMesh surface;
};

#endif