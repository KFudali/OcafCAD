#ifndef NetgenMeshEngine_hpp
#define NetgenMeshEngine_hpp

#ifndef OCCGEOMETRY
#define OCCGEOMETRY
#endif

#include <occgeom.hpp>
#include <meshing.hpp>

#include <memory>

#include "AbstractMeshEngine.hpp"
#include "SurfaceMesh.hpp"
#include "VolumeMesh.hpp"

class MeshPreprocessor;
class MeshPostprocessor;
class MeshingLauncher;
class NetgenMeshEngine : public AbstractMeshEngine {
    public:
    NetgenMeshEngine() = default;

    bool generateSurfaceMesh(MeshObject& aMeshObject) const override;
    bool generateVolumeMesh(MeshObject& aMeshObject) const override;

    private:
    std::unique_ptr<MeshPreprocessor> mMeshPre;
    std::unique_ptr<MeshingLauncher> mMeshingLauncher;
    std::unique_ptr<MeshPostprocessor> mMeshPost;
};



#endif