#ifndef PartDocument_hpp
#define PartDocument_hpp

#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>
#include <memory>

#include "RootAssembly.hpp"
#include "PrototypeRegistry.hpp"
#include "DocLabel.hpp"
#include "Part.hpp"
#include "PartLabel.hpp"
#include "PartPrototype.hpp"
#include "PrototypeLabel.hpp"

class DocumentGeometry {
    public:
    DocumentGeometry(Handle(TDocStd_Document) aDoc);
    inline Handle(TDocStd_Document) data() {return mDoc;};
    
    inline DocLabel rootAssemblyLabel() const {return mRootAssembly->label();};
    
    PartLabel addEmptyPart(); 
    PartLabel addEmptyAssembly(); 
    PartLabel addPart(PrototypeLabel aPrototype, Location aLocation); 
    PrototypeLabel addPrototype(PartPrototype aPrototype);
    PrototypeLabel addAssemblyPrototype(PartPrototype aPrototype);
    
    std::vector<PrototypeLabel> prototypes() const;
    std::vector<PartLabel> topLevelParts() const; 
    std::vector<PartLabel> freeParts() const; 
   
    private:
    Handle(XCAFDoc_ShapeTool) mShapeTool;
    Handle(TDocStd_Document) mDoc;

    std::unique_ptr<RootAssembly> mRootAssembly;
    std::unique_ptr<PrototypeRegistry> mPrototypeRegistry;
};

#endif