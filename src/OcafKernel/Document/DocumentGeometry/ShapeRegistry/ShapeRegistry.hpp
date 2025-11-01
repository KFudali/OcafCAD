#ifndef PrototypeRegistry_hpp
#define PrototypeRegistry_hpp

#include "ShapeLabel.hpp"
#include "Shape.hpp"

#include <Standard_Handle.hxx>
#include <TDocStd_Document.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>

class ShapeRegistry {

    public:
    ShapeRegistry(Handle(TDocStd_Document) aDoc);
    ~ShapeRegistry() = default;

    ShapeLabel addPrototype(Shape aShape);
    ShapeLabel addAssemblyPrototype(Shape aShape);
    bool removePrototype(ShapeLabel aPrototypeLabel);

    std::vector<ShapeLabel> prototypeList() const; 

    private:
    Handle(TDocStd_Document) mDoc;
    Handle(XCAFDoc_ShapeTool) mShapeTool;
};


#endif