#ifndef PartPrototypes_hpp
#define PartPrototypes_hpp

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>

#include <memory>
#include <vector>

namespace StubPartPrototypes{
    inline TopoDS_Shape cube() {
        return BRepPrimAPI_MakeBox(1.0, 1.0, 1.0).Shape();
    }

    inline TopoDS_Shape sphere() {
        return BRepPrimAPI_MakeSphere(1.0).Shape();
    }
}

#endif