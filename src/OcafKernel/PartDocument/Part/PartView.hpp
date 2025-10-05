#ifndef PartView_hpp
#define PartView_hpp

#include "Part.hpp"

class PartView {
    public:
    PartView(const PartLabel& aPartLabel) : mPart(Part(aPartLabel)) {};
    ~PartView() = default;    

    ColorRGBA color() const {return mPart.color();};
    std::string name() const {return mPart.name();};
    Location location() const {return mPart.location();};

    PartPrototype prototype() const {return mPart.prototype();};

    bool isAssembly() const {return mPart.isAssembly();};
    bool isComponent() const {return mPart.isComponent();};

    PartLabel parentAssembly() const {return mPart.parentAssembly();};
    std::vector<PartLabel> childrenComponents() const {return mPart.childrenComponents();};

    private:
    Part mPart;
};

#endif

