#ifndef GeometryPart_hpp
#define GeometryPart_hpp

#include "Part.hpp"

class GeometryPart : public Part {
    public:
    GeometryPart(const PartLabel& aPartLabel);
    virtual ~GeometryPart() = default;
    
    bool setLocation(const Location& aLocation);
    bool setPrototype(const PartPrototype& aName);

    PartLabel addEmptyComponent();

    bool expandToAssembly();

    PartLabel addComponent(
        PartLabel aPartLabel, 
        Location aLocation
    );
    PartLabel addComponent(
        PrototypeLabel aPartLabel, 
        Location aLocation
    );
    bool removeComponent(PartLabel aPartLabel);
};


#endif