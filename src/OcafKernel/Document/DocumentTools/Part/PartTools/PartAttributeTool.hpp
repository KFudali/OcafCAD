#ifndef PartAttributeTool_hpp
#define PartAttributeTool_hpp

#include "PartLabel.hpp"
#include "ColorRGBA.hpp"

#include <string>
#include <stdexcept>

class PartDoesNotHaveAttribute : public std::runtime_error {
    public:
    PartDoesNotHaveAttribute(const std::string& message)
    : std::runtime_error(message) {}
};

class PartAttributeTool {
    public:
    PartAttributeTool(const PartLabel& aPartLabel) : mPartLabel(aPartLabel) {}

    std::string name() const;
    ColorRGBA color() const;
    int layer() const;

    bool setName(const std::string& aNewName);
    bool setColor(const ColorRGBA& aNewColor) const;
    bool setLayer(int newLayer) const;

    private:
    PartLabel mPartLabel; 

};

#endif