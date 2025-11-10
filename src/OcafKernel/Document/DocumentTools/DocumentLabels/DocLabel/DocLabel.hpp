#ifndef DocLabel_HPP
#define DocLabel_HPP

#include <TDF_Label.hxx>
#include <string>
#include <vector>
#include <stdexcept>

class LabelException : public std::exception {
public:
    explicit LabelException(std::string msg)
        : mMsg(std::move(msg)) {}

    const char* what() const noexcept override {
        return mMsg.c_str();
    }
private:
    std::string mMsg;
};

class DocLabel {
    public: 
    DocLabel() : mLabel() {};
    DocLabel(TDF_Label aLabel);

    bool operator==(const DocLabel& aOther) const {
        return mLabel.IsEqual(aOther.mLabel);
    }
    bool operator!=(const DocLabel& aOther) const {
        return !mLabel.IsEqual(aOther.mLabel);
    }

    bool isValid() const { return !mLabel.IsNull(); };
    TDF_Label label() const { return mLabel; }    

    std::vector<int> toIntVector() const;
    std::string toString() const;

    protected:
    TDF_Label mLabel;
};

#endif