#ifndef Part_hpp
#define Part_hpp

#include "PartLabel.hpp"
#include "PartTools.hpp"

class Part{
    public:
    inline static ColorRGBA defaultPartColor = ColorRGBA();
    inline static std::string defaultPartName = "PartName";
    
    Part(
        PartLabel aPartLabel
    );
    
    ~Part() = default;

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

    bool addComponent(PartLabel aPartLabel); 
    bool removeComponent(PartLabel aPartLabel);

    std::vector<PartLabel> childrenComponents() const;
    PartLabel parentAssembly() const;

    private:
    PartLabel mPartLabel;
    PartTools mPartTools;
};


#endif