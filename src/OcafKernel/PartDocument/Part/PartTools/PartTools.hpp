#ifndef PartTools_hpp
#define PartTools_hpp

#include <memory>
#include "AbstractPartAssemblyTool.hpp"
#include "AbstractPartAttributeTool.hpp"
#include "AbstractPartGeometryTool.hpp"

class PartTools {
    public:
    PartTools(
        std::unique_ptr<AbstractPartGeometryTool> aGeometryTool,
        std::unique_ptr<AbstractPartAssemblyTool> aAssemblyTool,
        std::unique_ptr<AbstractPartAttributeTool> aAttributesTool
    ) : mGeometryTool(std::move(aGeometryTool)),
        mAssemblyTool(std::move(aAssemblyTool)),
        mAttributesTool(std::move(aAttributesTool)) {}
    ~PartTools() = default;

    inline AbstractPartGeometryTool& geometry() const {
        return *mGeometryTool;
    };
    inline AbstractPartAssemblyTool& assembly() const {
        return *mAssemblyTool;
    };
    inline AbstractPartAttributeTool& attributes() const {
        return *mAttributesTool;
    };

    private:    
    std::unique_ptr<AbstractPartGeometryTool> mGeometryTool;
    std::unique_ptr<AbstractPartAssemblyTool> mAssemblyTool;
    std::unique_ptr<AbstractPartAttributeTool> mAttributesTool;
};

#endif