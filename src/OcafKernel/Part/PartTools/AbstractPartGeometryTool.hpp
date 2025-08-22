#ifndef AbstractPartGeometryTool_hpp
#define AbstractPartGeometryTool_hpp

#include "Location.hpp"
#include "PartPrototype.hpp"

class AbstractPartGeometryTool{
    public:
    virtual ~AbstractPartGeometryTool() = default;
    virtual bool setLocation(Location aLocation) = 0;
    virtual bool setPrototype(PartPrototype aPrototype) = 0;
    virtual PartPrototype prototype() const = 0;
    virtual Location location() const = 0;
};

#endif