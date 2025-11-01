#ifndef DocumentGeometry_hpp
#define DocumentGeometry_hpp

#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>
#include <memory>

#include "RootAssembly.hpp"
#include "ShapeRegistry.hpp"
#include "DocLabel.hpp"
#include "Part.hpp"
#include "PartLabel.hpp"
#include "Shape.hpp"
#include "ShapeLabel.hpp"

class DocumentGeometry {
    public:
    DocumentGeometry(Handle(TDocStd_Document) aDoc);
    inline Handle(TDocStd_Document) data() {return mDoc;};
    
    inline DocLabel rootAssemblyLabel() const {return mRootAssembly->label();};
    
    PartLabel addEmptyPart(); 
    PartLabel addEmptyAssembly(); 
    PartLabel addPart(ShapeLabel aPrototype, Location aLocation); 
    ShapeLabel addPrototype(Shape aPrototype);
    ShapeLabel addAssemblyPrototype(Shape aPrototype);
    
    std::vector<ShapeLabel> prototypes() const;
    std::vector<PartLabel> topLevelParts() const; 
    std::vector<PartLabel> freeParts() const; 
   
    private:
    Handle(XCAFDoc_ShapeTool) mShapeTool;
    Handle(TDocStd_Document) mDoc;

    std::unique_ptr<RootAssembly> mRootAssembly;
    std::unique_ptr<ShapeRegistry> mPrototypeRegistry;
};

#endif