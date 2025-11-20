#include <gmock/gmock.h>

#include <occgeom.hpp>
#include <meshing.hpp>

#include <vtkType.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>

#include <vector>

#include "SurfaceExtraction.hpp"




// Offsets:      {0, 3, 6, 10, 12}
// Connectivity: {0, 1, 2, 5, 7, 2, 3, 4, 6, 7, 5, 8}