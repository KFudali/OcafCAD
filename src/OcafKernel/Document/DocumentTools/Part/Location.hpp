#ifndef Location_hpp
#define Location_hpp

#include <TopLoc_Location.hxx>

using Location  = TopLoc_Location;

namespace LocationUtils{
    inline bool LocationTrsfEqual(
        const Location& lhs, 
        const Location& rhs, 
        double tol = 1e-12
    ){
        const gp_Trsf& t1 = lhs.Transformation();
        const gp_Trsf& t2 = rhs.Transformation();

        for (int r = 1; r <= 3; ++r)
        {
            for (int c = 1; c <= 4; ++c)
            {
                if (std::abs(t1.Value(r, c) - t2.Value(r, c)) > tol)
                    return false;
            }
        }
        return true;
    }
}

#endif