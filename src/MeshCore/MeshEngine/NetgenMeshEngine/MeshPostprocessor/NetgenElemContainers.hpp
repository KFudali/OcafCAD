#ifndef NetgenElemContainers_hpp
#define NetgenElemContainers_hpp

#include <meshing.hpp>

using Elem2DContainer = ngcore::Array<netgen::Element2d, netgen::SurfaceElementIndex>;
using Elem3DContainer = ngcore::Array<netgen::Element, netgen::SurfaceElementIndex>;

#endif