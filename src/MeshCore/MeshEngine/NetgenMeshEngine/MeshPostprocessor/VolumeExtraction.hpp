#ifndef VolumeExtraction_hpp
#define VolumeExtraction_hpp

#include <meshing.hpp>
#include <occgeom.hpp>
#include <memory>
#include <vector>

#include "MeshExtractionUtils.hpp"
#include "VolumeConnectivity.hpp"
#include "Points.hpp"

namespace VolumeExtraction{

    VolumeConnectivity extractVolumeConnectivity(
        std::shared_ptr<netgen::Mesh> aNetgenMesh
    )

};

#endif