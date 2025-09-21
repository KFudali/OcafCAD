#ifndef StubSTEPFileSources_hpp
#define StubSTEPFileSources_hpp

#include "FileSource.hpp"

namespace StubSTEPFileSources {

    FileSource singlePartCube() {
        return FileSource(std::string(TEST_DATA_DIR));
    }

};

#endif