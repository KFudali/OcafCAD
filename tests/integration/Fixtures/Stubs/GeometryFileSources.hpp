#ifndef GeometryFileSources_hpp
#define GeometryFileSources_hpp

#include "FileSource.hpp"

namespace STEPFiles {
    FileSource singlePartCube() {
        std::string cubePath = std::string(TEST_DATA_DIR) + "/cube.stp";
        return FileSource(std::string(cubePath));
    }

    FileSource singleAssemblyJoint() {
        std::string joinPath = std::string(TEST_DATA_DIR) + "/joint.stp";
        return FileSource(std::string(joinPath));
    }
};

#endif