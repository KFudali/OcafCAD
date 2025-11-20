#ifndef SurfaceExtraction_hpp
#define SurfaceExtraction_hpp


#include <meshing.hpp>
#include <occgeom.hpp>
#include <memory>
#include <vector>

#include "MeshExtractionUtils.hpp"
#include "SurfaceConnectivity.hpp"
#include "Points.hpp"

namespace SurfaceExtraction {
    SurfaceConnectivity extractSurfaceConnectivity(
        std::shared_ptr<netgen::Mesh> aNetgenMesh
    );
}


#endif