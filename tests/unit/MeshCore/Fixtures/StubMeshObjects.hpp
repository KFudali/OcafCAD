#ifndef StubMeshObjects_hpp
#define StubMeshObjects_hpp

#include "StubGeometryObjects.hpp"
#include "MeshObject.hpp"

namespace StubMeshObjects {

    MeshObject cubeObject() {
        auto cubeGeoPtr = std::make_shared<GeometryObject>(
            StubGeometryObjects::cubeObject()
        );
        return MeshObject(std::move(cubeGeoPtr));
    }
    MeshObject sphereObject() {
        auto sphereGeoPtr = std::make_shared<GeometryObject>(
            StubGeometryObjects::sphereObject()
        );
        return MeshObject(std::move(sphereGeoPtr));
    }
};

#endif