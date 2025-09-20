#ifndef AbstractProgressScope_hpp
#define AbstractProgressScope_hpp

#include <memory>
#include <string>
#include <vector>

#include "Fraction.hpp"

class ProgressRange {
    public:
    ProgressRange(const std::string& aLabel);

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

    inline std::optional<std::reference_wrapper<ProgressRange>> parentRange() const {
        if (mParent) return *mParent; return std::nullopt;
    }

    inline std::vector<std::reference_wrapper<ProgressRange>> childrenRanges() const {
        std::vector<std::reference_wrapper<ProgressRange>> result;
        for (const auto& child : mChildren) {
            result.push_back(*child);
        }
        return result;
    }

    inline bool finalized() const {return mFinalized;}

    ProgressRange& createSubRange(
        const std::string& aLabel,
        const Fraction& aWeight
    );
    ProgressRange& createSubRange(
        const std::string& aLabel
    );
    
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
    std::vector<std::unique_ptr<ProgressRange>> mChildren;
};

#endif