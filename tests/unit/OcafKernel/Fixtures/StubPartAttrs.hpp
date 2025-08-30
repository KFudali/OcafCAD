#ifndef StubPartAttrs_hpp
#define StubPartAttrs_hpp

#include <TopLoc_Location.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>

namespace StubPartAttrs {

    using Location = TopLoc_Location;

    inline Location location(float x, float y, float z) {
        gp_Trsf trsf;
        trsf.SetTranslation(gp_Vec(x, y, z));
        return Location(trsf);
    }

}

#endif
