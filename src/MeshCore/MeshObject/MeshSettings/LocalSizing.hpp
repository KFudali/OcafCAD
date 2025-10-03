#ifndef LocalSizing_hpp
#define LocalSizing_hpp

#include "ShapeIds.hpp"

template <ShapeType T>
struct LocalSizing {
    TypedSubShapeId target;
    float minSize, maxSize;

    LocalSizing(int id, float min, float max)
        : target{id, T}, minSize(min), maxSize(max) {}
};

using EdgeSizing   = LocalSizing<ShapeType::TopAbs_EDGE>;
using FaceSizing   = LocalSizing<ShapeType::TopAbs_FACE>;
using VolumeSizing = LocalSizing<ShapeType::TopAbs_SOLID>;

#endif