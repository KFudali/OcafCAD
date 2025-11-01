#ifndef GeometryNamedSelection_hpp
#define GeometryNamedSelection_hpp

#include <string>
#include <TDF_Label.hxx>

class GeometryNamedSelection {
    public:
    GeometryNamedSelection(
        TDF_Label aParentLabel,
        TDF_Label aSubShapeLabel,
        const std::string& aName
    );
    GeometryNamedSelection(TDF_Label aNamingLabel);
    
    std::string name() const; 
    inline TDF_Label label() const {return mLabel;}; 
    
    bool rename(const std::string& aNewName);     

    private:
    TDF_Label findExistingNamedSelection(
        const TDF_Label& aParentLabel,
        const TDF_Label& aSubShapeLabel
    ) const;
    
    TDF_Label mLabel;
};

#endif