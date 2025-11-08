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
        mGlobalSettings(std::make_unique<GlobalMeshSettings>()){}
    
    inline const GeometryObject& geometry() const {return *mGeometryObject;};

    inline LocalMeshSettings& localSettings() const {return *mLocalSettings;}
    inline GlobalMeshSettings& globalSettings() const {return *mGlobalSettings;} 

    private:
    std::shared_ptr<GeometryObject> mGeometryObject;
    std::unique_ptr<LocalMeshSettings> mLocalSettings;
    std::unique_ptr<GlobalMeshSettings> mGlobalSettings;
};

#endif