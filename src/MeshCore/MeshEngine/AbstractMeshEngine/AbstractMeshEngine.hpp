#ifndef AbstractMeshEngine_hpp
#define AbstractMeshEngine_hpp

#include "MeshObject.hpp"

class AbstractMeshEngine {
    public:
    AbstractMeshEngine() = default;
    virtual ~AbstractMeshEngine() = default;

    virtual bool generateSurfaceMesh(MeshObject& aMeshObject) const = 0;
    virtual bool generateVolumeMesh(MeshObject& aMeshObject) const = 0;

    private:
};

#endif