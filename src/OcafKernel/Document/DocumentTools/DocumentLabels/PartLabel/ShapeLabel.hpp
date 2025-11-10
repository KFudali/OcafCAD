#ifndef PrototypeLabel_hpp
#define PrototypeLabel_hpp  

#include "DocLabel.hpp"

class LabelIsNotAShapeLabel : public std::exception {
public:
    explicit LabelIsNotAShapeLabel(std::string msg)
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
    static bool isShapeLabel(TDF_Label aLabel);
};

#endif