#ifndef PartLabel_hpp
#define PartLabel_hpp

#include <TDF_Label.hxx>
#include <string>
#include <vector>
#include <stdexcept>

class LabelDoesNotReferenceShape : public std::exception {
public:
    const char* what() const noexcept override {
        return "TDF_Label does not reference a shape.";
    }
};

class PartLabel {
    public: 
    PartLabel() : mLabel() {};
    PartLabel(TDF_Label aLabel);

    TDF_Label label() const { return mLabel; }    

    std::vector<int> toIntVector() const;
    std::string toString() const;

    private:
    TDF_Label mLabel;
};

#endif