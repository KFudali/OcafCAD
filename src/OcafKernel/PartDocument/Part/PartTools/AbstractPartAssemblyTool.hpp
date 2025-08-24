#ifndef AbstractPartAssemblyTool_hpp
#define AbstractPartAssemblyTool_hpp

#include "PartLabel.hpp"

class AbstractPartAssemblyTool{
    public:
    virtual ~AbstractPartAssemblyTool() = default;  
    virtual bool isAssembly() const = 0;
    virtual bool isComponent() const = 0;

    virtual std::vector<PartLabel> childrenComponents() const = 0;
    virtual PartLabel parentAssembly() const = 0;

    virtual bool addComponent(PartLabel aPartLabel) = 0; 
    virtual bool removeComponent(PartLabel aPartLabel) = 0;
};

#endif