#ifndef Dim_hpp
#define Dim_hpp

#include "Shape.hpp"

enum class Dim {
    D1 = 1,
    D2 = 2,
    D3 = 3
};

namespace DimUtils{
    inline Dim determineDim(const Shape& aShape) {
        switch (aShape.ShapeType()) {
            case TopAbs_VERTEX:
            case TopAbs_EDGE:
                return Dim::D1;

            case TopAbs_WIRE:
            case TopAbs_FACE:
            case TopAbs_SHELL:
                return Dim::D2;

            case TopAbs_SOLID:
            case TopAbs_COMPSOLID:
            case TopAbs_COMPOUND:
                return Dim::D3;

            default:
                return Dim::D3;
        }
    }
};



#endif