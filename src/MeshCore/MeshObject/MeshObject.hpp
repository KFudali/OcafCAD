#ifndef MeshObject_hpp
#define MeshObject_hpp

#include "GeometryObject.hpp"

#include <memory>

#include "LocalMeshSettings.hpp"
#include "GlobalMeshSettings.hpp"
#include "Mesh3D.hpp"

class MeshObject {
    public:
    MeshObject(std::shared_ptr<GeometryObject> aGeometryObject)
      : mGeometryObject(aGeometryObject),
        mLocalSettings(std::make_unique<LocalMeshSettings>()),
        mGlobalSettings(std::make_unique<GlobalMeshSettings>()){}
    
    inline GeometryObject& geometry() const {return *mGeometryObject;};

    inline LocalMeshSettings& localSettings() const {return *mLocalSettings;}
    inline GlobalMeshSettings& globalSettings() const {return *mGlobalSettings;} 

	inline bool hasSurfaceMesh() const {return false;}	
	inline bool hasMesh() const {return false;}	
    inline Mesh3D& mesh() const {return *mMesh;} 

    private:
    
    

    std::shared_ptr<GeometryObject> mGeometryObject;

    std::unique_ptr<LocalMeshSettings> mLocalSettings;
    std::unique_ptr<GlobalMeshSettings> mGlobalSettings;
    std::unique_ptr<Mesh3D> mMesh;
};

#endif