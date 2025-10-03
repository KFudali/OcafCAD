#ifndef StubGeometryObject_hpp
#define StubGeometryObject_hpp

#include "StubPartDocument.hpp"
#include "StubPartPrototypes.hpp"
#include "GeometryObject.hpp"

namespace StubGeometryObjects {

    GeometryObject cubeObject() {
        auto partDoc = StubPartDocument::partDocument();
        auto cubeProto = StubPartPrototypes::cube();
        auto protoLabel = partDoc.addPrototype(cubeProto);
        auto partLabel = partDoc.addPart(protoLabel, Location());
        return GeometryObject(partLabel);
    }
    GeometryObject sphereObject() {
        auto partDoc = StubPartDocument::partDocument();
        auto cubeProto = StubPartPrototypes::sphere();
        auto protoLabel = partDoc.addPrototype(cubeProto);
        auto partLabel = partDoc.addPart(protoLabel, Location());
        return GeometryObject(partLabel);
    }
}

#endif