#include "Part.hpp"
#include "PartAssemblyTool.hpp"
#include "PartAttributeTool.hpp"
#include "PartGeometryTool.hpp"
#include <stdexcept>

Part::Part(PartLabel aPartLabel)
    : mPartLabel(aPartLabel),
      mPartTools(
          std::make_unique<PartGeometryTool>(aPartLabel),
          std::make_unique<PartAssemblyTool>(aPartLabel),
          std::make_unique<PartAttributeTool>(aPartLabel)) 
{
    if (!mPartTools.attributes().hasColor()) {
        setColor(Part::defaultPartColor);
    }
    if (!mPartTools.attributes().hasName()) {
        setName(Part::defaultPartName);
    }
}

Part::Part(const Part& other)
    : mPartLabel(other.mPartLabel),
      mPartTools(
          std::make_unique<PartGeometryTool>(other.mPartLabel),
          std::make_unique<PartAssemblyTool>(other.mPartLabel),
          std::make_unique<PartAttributeTool>(other.mPartLabel)) 
{
    if (!mPartTools.attributes().hasColor()) {
        setColor(Part::defaultPartColor);
    }
    if (!mPartTools.attributes().hasName()) {
        setName(Part::defaultPartName);
    }
}

bool Part::isAssembly() const {
    return mPartTools.assembly().isAssembly();
}
bool Part::isComponent() const {
    return mPartTools.assembly().isComponent();
}

PartLabel Part::addEmptyComponent() {
    return mPartTools.assembly().addEmptyComponent();
}

bool Part::expandToAssembly(){return mPartTools.assembly().expandToAssembly();};    

PartLabel Part::addComponent(
    PartLabel aPartLabel, 
    Location aLocation
){
    return mPartTools.assembly().addComponent(aPartLabel, aLocation);
}
PartLabel Part::addComponent(
    PrototypeLabel aProtoLabel, 
    Location aLocation
){
    return mPartTools.assembly().addComponent(aProtoLabel, aLocation);
}
bool Part::removeComponent(PartLabel aPartLabel){
    return mPartTools.assembly().removeComponent(aPartLabel);
}

std::vector<PartLabel> Part::childrenComponents() const{
    return mPartTools.assembly().childrenComponents();
};
PartLabel Part::parentAssembly() const{
    return mPartTools.assembly().parentAssembly();
};

std::string Part::name() const {
    return mPartTools.attributes().name();
}
ColorRGBA Part::color() const {
    return mPartTools.attributes().color(); 
}

Location Part::location() const{
    return mPartTools.geometry().location();
}
PartPrototype Part::prototype() const {
    return mPartTools.geometry().prototype();
};

bool Part::setName(const std::string& aName) {
    return mPartTools.attributes().setName(aName);
}
bool Part::setColor(const ColorRGBA& aColor) {
    return mPartTools.attributes().setColor(aColor);
}

bool Part::setLocation(const Location& aLocation) {
    return mPartTools.geometry().setLocation(aLocation);
}
bool Part::setPrototype(const PartPrototype& aPrototype) {
    return mPartTools.geometry().setPrototype(aPrototype);
}   