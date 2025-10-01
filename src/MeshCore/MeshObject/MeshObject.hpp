#ifndef MeshObject_hpp
#define MeshObject_hpp

#include "GeometryObject.hpp"
#include <memory>



class MeshObject {
    public:
    MeshObject(std::shared_ptr<GeometryObject> aGeometryObject);


    

    private:
    std::shared_ptr<GeometryObject> mGeometryObject;
};

#endif