#ifndef STEPImporterExceptions_hpp
#define STEPImporterExceptions_hpp

#include <stdexcept>
#include <string>

namespace STEPImporterExceptions {

class CouldNotReadSTEPFile : public std::runtime_error {
public:
    explicit CouldNotReadSTEPFile(const std::string& msg)
        : std::runtime_error("Could not read STEP file: " + msg) {}
};

}

#endif