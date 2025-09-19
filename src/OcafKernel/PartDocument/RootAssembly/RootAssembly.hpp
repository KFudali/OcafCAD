#ifndef RootAssembly_hpp
#define RootAssembly_hpp

#include "DocLabel.hpp"
#include "PartLabel.hpp"
#include "PrototypeLabel.hpp"
#include "Location.hpp"

#include <TDocStd_Document.hxx>
#include <TDF_Label.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>

class RootAssembly {

    public:
    RootAssembly(Handle(TDocStd_Document) aDoc);
    ~RootAssembly() = default;

    static bool isRootAssembly(TDF_Label aLabel);

    void clear(); 
    
    PartLabel addPart(PrototypeLabel aPrototypeLabel, Location aLocation);
    PartLabel addEmptyAssembly();
    PartLabel addEmptyPart();
    
    void removePart(PartLabel aPartLabel);
    
    std::vector<PartLabel> freeParts() const;
    std::vector<PartLabel> topLevelParts() const;
    inline DocLabel label() const {return mLabel;};

    private:

    DocLabel mLabel;
    Handle(TDocStd_Document) mDoc;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};

#endif