#ifndef NamedRefTreeLabel_hpp
#define NamedRefTreeLabel_hpp

#include <string>
#include <TDF_Label.hxx>
#include <TDF_LabelSequence.hxx>
#include "RefTreeLabel.hpp"

class NamedRefTreeLabel : public RefTreeLabel {
    public:
    NamedRefTreeLabel(
        const TDF_Label& aParentLabel,
        const TDF_LabelSequence& aSubShapeLabels,
        const std::string& aName
    );
    NamedRefTreeLabel(TDF_Label aNamedRefTreeLabel);
    NamedRefTreeLabel(const NamedRefTreeLabel& other)
        : RefTreeLabel(other.label()){}
    NamedRefTreeLabel& operator=(const NamedRefTreeLabel& other) {
        if (this != &other) {mLabel = other.label();}
        return *this;
    }
    
    std::string name() const; 
    bool rename(const std::string& aNewName);     
    
    private:
};

#endif