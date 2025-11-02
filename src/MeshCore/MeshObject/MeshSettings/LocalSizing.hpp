#ifndef LocalSizing_hpp
#define LocalSizing_hpp

#include "SubShapeId.hpp"
#include "ShapeType.hpp"

template <int T>
struct LocalSizing {
    SubShapeId target;
    float minSize, maxSize;

    LocalSizing(const SubShapeId& id, float min, float max)
        : target(id), minSize(min), maxSize(max) {}
};

using EdgeSizing   = LocalSizing<TopAbs_EDGE>;
using FaceSizing   = LocalSizing<TopAbs_FACE>;
using VolumeSizing = LocalSizing<TopAbs_SOLID>;

#endif
