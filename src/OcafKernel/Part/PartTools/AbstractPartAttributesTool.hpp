#ifndef AbstractPartAttributesTool_hpp
#define AbstractPartAttributesTool_hpp

#include <string>
#include "ColorRGBA.hpp"

class AbstractPartAttributesTool{
    public:
    virtual ~AbstractPartAttributesTool() = default;
    
    virtual bool hasColor() const = 0;
    virtual bool hasName() const = 0;

    virtual bool setColor(const ColorRGBA& aColor) = 0;
    virtual bool setName(const std::string& aName) = 0;
    virtual ColorRGBA color() const = 0;
    virtual std::string name() const = 0;
};

#endif