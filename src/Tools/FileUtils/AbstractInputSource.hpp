#ifndef AbstractInputSource_hpp
#define AbstractInputSource_hpp

#include <string>
#include <istream>

class AbstractInputSource {
    public:
    virtual ~AbstractInputSource() = default;
    virtual std::istream& stream() = 0;
    virtual std::string name() = 0;
};

#endif