#ifndef NamedSelectionLabel_hpp
#define NamedSelectionLabel_hpp

#include <string>
#include <TDF_Label.hxx>

class NamedSelectionLabel {
    public:
    NamedSelectionLabel(
        TDF_Label aParentLabel,
        TDF_Label aSubShapeLabel,
        const std::string& aName
    );
    NamedSelectionLabel(TDF_Label aNamingLabel);
    
    std::string name() const; 
    inline TDF_Label label() const {return mLabel;}; 
    TDF_Label referredLabel() const; 
    bool rename(const std::string& aNewName);     

    bool operator==(const NamedSelectionLabel& other) const{
        return mLabel.IsEqual(other.mLabel);
    }
    bool operator!=(const NamedSelectionLabel& other) const{
        return !(*this == other);
    }

    private:
    TDF_Label findExistingNamedSelection(
        const TDF_Label& aParentLabel,
        const TDF_Label& aSubShapeLabel
    ) const;
    
    TDF_Label mLabel;
};

#endif