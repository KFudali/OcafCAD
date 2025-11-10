#ifndef SubShapeLabel_hpp
#define SubShapeLabel_hpp  

#include "DocLabel.hpp"

class LabelIsNotASubShapeLabel : public std::exception {
public:
    explicit LabelIsNotASubShapeLabel(std::string msg)
        : mMsg(std::move(msg)) {}

    const char* what() const noexcept override {
        return mMsg.c_str();
    }
private:
    std::string mMsg;
};

class SubShapeLabel : public DocLabel {
    public: 
    SubShapeLabel() = default;
    SubShapeLabel(TDF_Label aLabel);
    static bool isSubShapeLabel(TDF_Label aLabel);
};

#endif