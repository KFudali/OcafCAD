#ifndef Part_hpp
#define Part_hpp

#include "PartLabel.hpp"
#include "PrototypeLabel.hpp"
#include "PartTools.hpp"

class Part{
    public:
    inline static ColorRGBA defaultPartColor = ColorRGBA();
    inline static std::string defaultPartName = "PartName";
    
    Part(
        PartLabel aPartLabel
    );
    
    virtual ~Part() = default;
    Part(const Part& other);

    inline PartLabel partLabel() const {return mPartLabel;}; 
    PartPrototype prototype() const;
    
    std::string name() const;
    ColorRGBA color() const;
    Location location() const; 

    bool setName(const std::string& aName);
    bool setColor(const ColorRGBA& aColor);
    
    bool setLocation(const Location& aLocation);
    bool setPrototype(const PartPrototype& aName);

    bool isAssembly() const;
    bool isComponent() const;

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

    std::vector<PartLabel> childrenComponents() const;
    PartLabel parentAssembly() const;

    protected:
    PartLabel mPartLabel;
    PartTools mPartTools;
};


#endif