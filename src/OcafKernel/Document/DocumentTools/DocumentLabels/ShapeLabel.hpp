#ifndef PrototypeLabel_hpp
#define PrototypeLabel_hpp  

#include "DocLabel.hpp"

class LabelIsNotAPrototypeLabel : public std::exception {
public:
    explicit LabelIsNotAPrototypeLabel(std::string msg)
        : mMsg(std::move(msg)) {}

    const char* what() const noexcept override {
        return mMsg.c_str();
    }
private:
    std::string mMsg;
};

class ShapeLabel : public DocLabel{
    public: 
    ShapeLabel() = default;
    ShapeLabel(TDF_Label aLabel);
    static bool isPrototypeLabel(TDF_Label aLabel);
};

#endif