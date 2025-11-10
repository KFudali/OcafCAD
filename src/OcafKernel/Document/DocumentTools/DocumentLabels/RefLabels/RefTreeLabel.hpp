#ifndef RefTreeLabel_hpp
#define RefTreeLabel_hpp

#include <string>
#include <TDF_Label.hxx>
#include <TDF_LabelSequence.hxx>
#include "DocLabel.hpp"

class RefTreeLabel : public DocLabel {
    public:
    RefTreeLabel(
        const TDF_Label& aParentLabel,
        const TDF_LabelSequence& aRefs
    );
    virtual ~RefTreeLabel() = default;

    RefTreeLabel(TDF_Label aRefTreeLabel);
    RefTreeLabel(const RefTreeLabel& other)
        : DocLabel(other.label()){}
    RefTreeLabel& operator=(const RefTreeLabel& other) {
        if (this != &other) {mLabel = other.label();}
        return *this;
    }

    virtual TDF_LabelSequence references() const;    
    virtual bool removeReference(const TDF_Label& aRefLabel);
    virtual bool appendReference(const TDF_Label& aRefLabel);

    private:

    TDF_Label addRef(const TDF_Label& aRefLabel);
};

#endif