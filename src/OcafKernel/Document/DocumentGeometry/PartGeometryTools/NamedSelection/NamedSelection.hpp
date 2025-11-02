#ifndef NamedSelection_hpp
#define NamedSelection_hpp

#include "NamedSelectionLabel.hpp"
#include "SubShapeId.hpp"

#include <string>

class NamedSelection {
    public:
    NamedSelection(const NamedSelectionLabel& aLabel);
   
    inline bool isValid() {return !mSelectionLabel.label().IsNull();} 
    inline NamedSelectionLabel label() const {return mSelectionLabel;}
    SubShapeId namedShapeId() const;
    
    inline std::string name() const {return mSelectionLabel.name();};
    inline bool rename(const std::string& aNewName) {
        return mSelectionLabel.rename(aNewName);
    }
    bool operator==(const NamedSelection& other) const{
        return mSelectionLabel == other.mSelectionLabel;
    }
    bool operator!=(const NamedSelection& other) const{
        return !(*this == other);
    }


    private:
    NamedSelectionLabel mSelectionLabel;
};

#endif