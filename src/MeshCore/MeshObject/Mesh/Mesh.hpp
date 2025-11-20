#ifndef Mesh_hpp
#define Mesh_hpp

#include "SurfaceMesh.hpp"
#include "VolumeMesh.hpp"

struct Mesh{
    Mesh(
        const SurfaceMesh& surface,
        const VolumeMesh& volume
    ) : surface(surface), volume(volume) {}
    
    SurfaceMesh surface;
    VolumeMesh volume;
};

#endif