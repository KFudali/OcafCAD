#ifndef MeshCore_hpp
#define MeshCode_hpp

class MeshCore {
    public:

    MeshObject createMeshObject(const GeometryObject& aGeoObject);

    private:

};

#endif

// MeshEntity
// Id
// Domain

// MeshPoint
// MeshFace
// MeshVolume

// MeshObject (GeometryObject) {

//     mesh() -> Mesh
//         MeshPoints
//         MeshFaces
//         MeshVoumes

//     addPointSetting -> bool
//     addEdgeSetting -> bool
//     addSurfaceSetting -> bool
//     addVolumeSetting ->bool

//     private
//     GeometryObject sourceObj
//     Mesh mesh

//     PointSettings
//     EdgeSettings
//     SurfaceSettings
//     VolumeSettings


// }

// GeometryObject(Part){

//     Points
//     Edges
//     Surfaces
//     Volumes  

// }



// #endif;