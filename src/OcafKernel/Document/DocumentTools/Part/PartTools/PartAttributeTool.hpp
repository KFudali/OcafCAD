#ifndef PartAttributeTool_hpp
#define PartAttributeTool_hpp

#include <Standard_Handle.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>

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
    PartAttributeTool(const PartLabel& aPartLabel);

    bool hasName() const;    
    bool hasColor() const;    

    std::string name() const;
    ColorRGBA color() const;
    // int layer() const;

    bool setName(const std::string& aNewName);
    bool setColor(const ColorRGBA& aNewColor);
    // bool setLayer(int newLayer) const;

    private:
    PartLabel mPartLabel; 
    Handle(XCAFDoc_ColorTool) mColorTool;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};

#endif