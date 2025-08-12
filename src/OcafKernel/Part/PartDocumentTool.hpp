#ifndef PartDocumentTool_hpp
#define PartDocumentTool_hpp

#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <TDF_Label.hxx>

class AbstractPartAttributesTool{
    public:
    bool setColor(const ColorRGBA& aColor) = 0;
    bool setName(const std::string& aName) = 0;
    Color color() const = 0;
    std::string name() const = 0;
};

class AbstractPartGeometryTool{
    public:
    bool setLocation(const Location& aLocation) = 0;
    bool setPrototype(const PratPrototype& aPrototype) = 0;
    PartPrototype prototype() const = 0;
    Location location() const = 0;
};

class AbstractPartAssemblyTool{
    public:
    bool isAssembly() const = 0;
    bool isComponent() const = 0;

    PartId parentAssembly() const = 0;
    std::vector<PartId> childrenComponents() const = 0;

    bool makeAssembly() = 0;
    
    bool removeComponent(const PartId& aPartId) = 0;
    Part addComponent(const PartPrototype& aPart, const Location& aLocation) = 0; 
    Part addEmptyComponent() = 0; 
};

class PartDocumentTool {
    public:
    PartDocumentTool(
        std::unique_ptr<AbstractPartGeometryTool> aGeometryTool,
        std::unique_ptr<AbstractPartAssemblyTool> aAssemblyTool
        std::unique_ptr<AbstractPartAttributesTool> aAttributesTool,
    ) : mGeometryTool(aGeometryTool),
        mAssemblyTool(aAssemblyTool),
        mAttributesTool(aAttributesTool) {}
    ~PartDocumentTool() = default;

    inline std::unique_ptr<AbstractPartGeometryTool> geometry() const {
        return mGeometryTool;
    };
    inline std::unique_ptr<AbstractPartAssemblyTool> assembly() const {
        return mAssemblyTool;
    };
    inline std::unique_ptr<AbstractPartAttributesTool> attributes() const {
        return mAttributesTool;
    };

    private:    
    std::unique_ptr<AbstractPartGeometryTool> mGeometryTool;
    std::unique_ptr<AbstractPartAssemblyTool> mAssemblyTool;
    std::unique_ptr<AbstractPartAttributesTool> mAttributesTool;
};

#endif