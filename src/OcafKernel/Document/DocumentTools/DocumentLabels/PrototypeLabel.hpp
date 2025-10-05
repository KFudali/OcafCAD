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

class PrototypeLabel : public DocLabel{
    public: 
    PrototypeLabel() = default;
    PrototypeLabel(TDF_Label aLabel);
    static bool isPrototypeLabel(TDF_Label aLabel);
};

#endif