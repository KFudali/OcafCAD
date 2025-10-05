#ifndef PartLabel_hpp
#define PartLabel_hpp

#include "DocLabel.hpp"

class LabelIsNotAPartLabel : public std::exception {
public:
    explicit LabelIsNotAPartLabel(std::string msg)
        : mMsg(std::move(msg)) {}

    const char* what() const noexcept override {
        return mMsg.c_str();
    }
private:
    std::string mMsg;
};

class PartLabel : public DocLabel {
    public: 
    PartLabel() = default;
    PartLabel(TDF_Label aLabel);

    static bool isPartLabel(TDF_Label aLabel);
};

#endif