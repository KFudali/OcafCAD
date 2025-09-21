#ifndef AbstractProgressScope_hpp
#define AbstractProgressScope_hpp

#include <memory>
#include <string>
#include <vector>

#include "Fraction.hpp"

class ProgressRange {
    public:
    ProgressRange(const std::string& aLabel = "Progress");

    void setLabel(const std::string& aNewLabel);
    void setTo(const Fraction& aFraction);
    void advanceBy(const Fraction& aFraction);
    void reset();
    void finalize();

    inline Fraction currentProgress() const {return mProgressFraction;}
    inline Fraction progressRemaining() const {return mProgressFraction.toGo();};
    inline Fraction remainingWeight() const {return mRemainingWeight;};
    inline Fraction weightInParent() const {return mWeightInParent;};
    inline std::string label() const {return mLabel;};

    inline std::optional<std::reference_wrapper<ProgressRange>> parent() const {
        if (mParent) return *mParent; return std::nullopt;
    }

    inline std::optional<std::reference_wrapper<ProgressRange>> child() const {
        if (mChild) return *mChild; return std::nullopt;
    }

    inline bool finalized() const {return mFinalized;}
    ProgressRange& newChild(
        const Fraction& aWeight,
        const std::string& aLabel = "Progress"
    );
    ProgressRange& newChild(
        const std::string& aLabel = "Progress"
    );

    void finalizeAndClearChild();
    
    private: 
    ProgressRange(
        ProgressRange* aParentRange,
        const std::string& aLabel,
        const Fraction& aWeightInParent
    );
    void advanceParentBy(const Fraction& aFraction);
    void advanceParentByFloat(float aFraction);
    void advanceByFloat(float aFraction);

    Fraction mRemainingWeight = Fraction(1.0);
    Fraction mProgressFraction = Fraction(0.0);
    std::string mLabel = "Progress" ;
    bool mFinalized = false; 
    
    const Fraction mWeightInParent = Fraction(1.0);
    
    ProgressRange* mParent = nullptr;
    std::unique_ptr<ProgressRange> mChild;
};

#endif