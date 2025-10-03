#ifndef MeshEngine_hpp
#define MeshEngine_hpp

#include "MeshObject.hpp"


class AbstractMeshEngine {
    public:
    AbstractMeshEngine() = default;
    virtual ~AbstractMeshEngine() = default;

    virtual bool generateSurfaceMesh(const MeshObject& aMeshObject) const = 0;
    virtual bool generateVolumeMesh(const MeshObject& aMeshObject) const = 0;

    private:
};

#endif