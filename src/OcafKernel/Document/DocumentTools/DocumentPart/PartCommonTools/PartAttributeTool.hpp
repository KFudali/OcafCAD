#ifndef PartAttributeTool_hpp
#define PartAttributeTool_hpp

#include "PartLabel.hpp"
#include "ColorRGBA.hpp"

#include <string>
#include <stdexcept>
#include <Standard_Handle.hxx>

class PartDoesNotHaveAttribute : public std::runtime_error {
    public:
    PartDoesNotHaveAttribute(const std::string& message)
    : std::runtime_error(message) {}
};


class XCAFDoc_ShapeTool;
class XCAFDoc_ColorTool;
class PartAttributeTool {
    public:
    PartAttributeTool(const PartLabel& aPartLabel);

    bool hasName() const;    
    bool hasColor() const;    

    std::string name() const;
    ColorRGBA color() const;

    bool setName(const std::string& aNewName);
    bool setColor(const ColorRGBA& aNewColor);

    private:
    PartLabel mPartLabel; 
    Handle(XCAFDoc_ColorTool) mColorTool;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};

#endif