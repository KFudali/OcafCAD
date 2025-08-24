#ifndef PartAttributeTool_hpp
#define PartAttributeTool_hpp

#include "PartLabel.hpp"
#include "AbstractPartAttributesTool.hpp"

#include <Standard_Handle.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>

#include <stdexcept>

class PartDoesNotHaveAttribute : public std::runtime_error {
    public:
    PartDoesNotHaveAttribute(const std::string& message)
    : std::runtime_error(message) {}
};

class PartAttributeTool : public AbstractPartAttributesTool {
    public:
    PartAttributeTool(PartLabel aPartLabel);


    std::string name() const override;
    ColorRGBA color() const override;

    bool setName(const std::string& aName) override;
    bool setColor(const ColorRGBA& aColor) override;

    private:
    bool hasName() const override;
    bool hasColor() const override;

    PartLabel mPartLabel;
    Handle(XCAFDoc_ColorTool) mColorTool;
    Handle(XCAFDoc_ShapeTool) mShapeTool;

};

#endif