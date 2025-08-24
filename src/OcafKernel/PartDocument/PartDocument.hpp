#ifndef PartDocument_hpp
#define PartDocument_hpp

#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>
#include <XCAFApp_Application.hxx>

#include "DocLabel.hpp"
#include "PartLabel.hpp"
#include "PrototypeLabel.hpp"

#include "RootAssembly.hpp"
#include "PartPrototype.hpp"
#include "Part.hpp"

class PartDocument {
    public:
    PartDocument(Handle(XCAFApp_Application) aXCAFApp);
    inline Handle(TDocStd_Document) data() {return mDoc;};
    
    inline DocLabel RootAssemblyLabel() const {return mRootAssembly->label();};
    
    Part addPart(PrototypeLabel aPrototype, Location aLocation); 
    PrototypeLabel addPrototype(PartPrototype aPrototype);
    
    std::vector<PrototypeLabel> prototypes() const;
    std::vector<PartLabel> freeParts() const; 
    
    private:
    Handle(XCAFApp_Application) mApp;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
    Handle(TDocStd_Document) mDoc;
    std::unique_ptr<RootAssembly> mRootAssembly;
};

#endif