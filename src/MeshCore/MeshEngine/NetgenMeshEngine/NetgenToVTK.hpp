#ifndef NetgetToVTK_hpp
#define NetgenToVTK_hpp

#include "Mesh.hpp"
#include <occgeom.hpp>
#include <meshing.hpp>

namespace NetgenToVTK {
    bool transfer(const netgen::Mesh& aSource, Mesh& aDest);
};

#endif