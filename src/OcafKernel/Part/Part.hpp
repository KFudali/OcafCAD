#ifndef Part_hpp
#define Part_hpp

#include "PartLabelKey.hpp"

class PartDocumentTool{
    public:
    PartDocumentTool(XCafDoc);
};

class Part{
    public:
    Part(
        PartLabel aPartLabel,
        PartDocumentTool aPartDocumentTool
    );
    ~Part() = default;

    PartLabelKey labelKey() const; 
    ShapePrototype shapePrototype() const;
    
    std::string name() const;
    ColorRGBA color() const;
    Location location() const; 

    bool setName(const std::string& aName);
    bool setColor(const ColorRGBA& aColor);
    bool setLocation(const Location& aLocation);

    private:
    PartLabelKey mPartLabelKey;
    PartDocumentTool mPartDocumentTool;
};
#endif