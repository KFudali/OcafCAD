#ifndef PartView_hpp
#define PartView_hpp

#include "Part.hpp"

class PartView {

    PartView(std::shared_ptr<const Part> aPart) : mPart(aPart) {};
    ~PartView() = default;    

    ColoRGBA color() const {return mPart->color();};
    std::string name() const {return mPart->name();};
    Location location() const {return mPart->location();};

    PartPrototype prototype() const {return mPart->partPrototype();};

    bool isAssembly() const {return mPart->isAssembly();};
    bool isComponent() const {return mPart->isComponent();};

    PartId parentAssembly() const {return mPart->parentAssembly();};
    std::vector<PartId> childrenComponents() const {return mPart->childrenComponents();};

    private:
    std::shared_ptr<const Part> mPart;
};

#endif