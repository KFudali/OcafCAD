#ifndef GeometryDocImporterExceptions_hpp
#define GeometryDocImporterExceptions_hpp

#include <stdexcept>

namespace GeometryDocImporterExceptions {

class CouldNotReadLabel : public std::runtime_error {
public:
    explicit CouldNotReadLabel(const std::string& msg)
        : std::runtime_error("Could not read TDFLabel: " + msg) {}
};

class CouldNotGetShapeFromLabel : public std::runtime_error {
public:
    explicit CouldNotGetShapeFromLabel(const std::string& msg)
        : std::runtime_error("Could not read TDFLabel: " + msg) {}
};


}


#endif