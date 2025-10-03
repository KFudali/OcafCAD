#ifndef LocalMeshSettings_hpp
#define LocalMeshSettings_hpp

#include "ShapeIds.hpp"
#include "LocalSizing.hpp"
#include <vector>
#include <stdexcept>

class LocalMeshSettings {
public:
    LocalMeshSettings() = default;

    void addEdgeSizing(TypedSubShapeId aId, float min, float max) {
        if (aId.shapeType != ShapeType::TopAbs_EDGE) {
            throw std::runtime_error("Cannot apply EdgeSizing to non-Edge");
        }
        mEdgeSizings.emplace_back(aId.idInParent, min, max);
    }

    void addFaceSizing(TypedSubShapeId aId, float min, float max) {
        if (aId.shapeType != ShapeType::TopAbs_FACE) {
            throw std::runtime_error("Cannot apply FaceSizing to non-Face");
        }
        mFaceSizings.emplace_back(aId.idInParent, min, max);
    }

    void addVolumeSizing(TypedSubShapeId aId, float min, float max) {
        if (aId.shapeType != ShapeType::TopAbs_SOLID) {
            throw std::runtime_error("Cannot apply VolumeSizing to non-Volume");
        }
        mVolumeSizings.emplace_back(aId.idInParent, min, max);
    }

private:
    std::vector<EdgeSizing> mEdgeSizings;
    std::vector<FaceSizing> mFaceSizings;
    std::vector<VolumeSizing> mVolumeSizings;
};

#endif
