#ifndef NetgenMeshEngine_hpp
#define NetgenMeshEngine_hpp

#include "AbstractMeshEngine.hpp"

#ifndef OCCGEOMETRY
#define OCCGEOMETRY
#endif

#include <occgeom.hpp>
#include <meshing.hpp>

class NetgenMeshEngine : public AbstractMeshEngine {
    public:
    NetgenMeshEngine() = default;

    bool generateSurfaceMesh(const MeshObject& aMeshObject) const override;
    bool generateVolumeMesh(const MeshObject& aMeshObject) const override;

    private:

};



#endif