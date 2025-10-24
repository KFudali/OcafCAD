#ifndef LocalMeshSettings_hpp
#define LocalMeshSettings_hpp

#include "SubShapeId.hpp"
#include "LocalSizing.hpp"
#include <vector>
#include <stdexcept>

class LocalMeshSettings {
public:
    LocalMeshSettings() = default;

    void addEdgeSizing(const TypedSubShapeId& id, float min, float max) {
        if (id.shapeType() != ShapeType::TopAbs_EDGE) {
            throw std::runtime_error("Cannot apply EdgeSizing to non-Edge");
        }
        mEdgeSizings.emplace_back(id, min, max);
    }

    void addFaceSizing(const TypedSubShapeId& id, float min, float max) {
        if (id.shapeType() != ShapeType::TopAbs_FACE) {
            throw std::runtime_error("Cannot apply FaceSizing to non-Face");
        }
        mFaceSizings.emplace_back(id, min, max);
    }

    void addVolumeSizing(const TypedSubShapeId& id, float min, float max) {
        if (id.shapeType() != ShapeType::TopAbs_SOLID) {
            throw std::runtime_error("Cannot apply VolumeSizing to non-Volume");
        }
        mVolumeSizings.emplace_back(id, min, max);
    }

private:
    std::vector<EdgeSizing> mEdgeSizings;
    std::vector<FaceSizing> mFaceSizings;
    std::vector<VolumeSizing> mVolumeSizings;
};

#endif
