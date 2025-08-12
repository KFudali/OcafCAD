#ifndef PartView_hpp
#define PartView_hpp

class PartView {

    ColoRGBA color() const;
    std::string name() const;
    Location location() const;

    PartPrototype shape() const;

    bool isAssembly() const;
    bool isComponent() const;

    PartId parentAssembly() const;
    std::vector<PartId> childrenComponents() const;    
};

#endif