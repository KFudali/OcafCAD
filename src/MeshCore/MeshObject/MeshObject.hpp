#ifndef MeshObject_hpp
#define MeshObject_hpp

#include "GeometryObject.hpp"
#include "LocalMeshSettings.hpp"
#include "GlobalMeshSettings.hpp"
#include "Mesh.hpp"
#include <memory>

class MeshObject {
    public:
    MeshObject(std::shared_ptr<GeometryObject> aGeometryObject)
      : mGeometryObject(aGeometryObject),
        mLocalSettings(std::make_unique<LocalMeshSettings>()),
        mGlobalSettings(std::make_unique<GlobalMeshSettings>()),
        mMesh(std::make_unique<Mesh>()) {}
    

    inline const GeometryObject& geometry() const {return *mGeometryObject;};
    inline LocalMeshSettings& localSettings() const {return *mLocalSettings;}
    inline GlobalMeshSettings& globalSettings() const {return *mGlobalSettings;}

    inline void setMesh(std::unique_ptr<Mesh> aMesh) {mMesh = std::move(aMesh);}
    inline Mesh& mesh() const {return *mMesh;}

    private:
    std::shared_ptr<GeometryObject> mGeometryObject;

    std::unique_ptr<LocalMeshSettings> mLocalSettings;
    std::unique_ptr<GlobalMeshSettings> mGlobalSettings;

    std::unique_ptr<Mesh> mMesh;
};

#endif