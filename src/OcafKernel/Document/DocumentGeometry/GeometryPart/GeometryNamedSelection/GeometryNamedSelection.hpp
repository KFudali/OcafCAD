#ifndef GeometryNamedSelection_hpp
#define GeometryNamedSelection_hpp

#include <string>
#include <TDF_Label.hxx>

class GeometryNamedSelection {
    public:
    GeometryNamedSelection(const std::string& aName, TDF_Label aSubShapeLabel);
   
    std::string name() const; 
    inline TDF_Label label() const {return mLabel;}; 
    
    bool rename(const std::string& aNewName);     

    private:    
    TDF_Label mLabel;
};

#endif