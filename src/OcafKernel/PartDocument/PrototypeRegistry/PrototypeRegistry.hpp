#ifndef PrototypeRegistry_hpp
#define PrototypeRegistry_hpp

#include "PrototypeLabel.hpp"
#include "PartPrototype.hpp"

#include <TDocStd_Document.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>

class PrototypeRegistry {

    public:
    PrototypeRegistry(Handle(TDocStd_Document) aDoc);
    ~PrototypeRegistry() = default;

    PrototypeLabel addPrototype(PartPrototype aShape);
    bool removePrototype(PrototypeLabel aPrototypeLabel);

    std::vector<PrototypeLabel> prototypeList() const; 

    private:
    Handle(TDocStd_Document) mDoc;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};


#endif