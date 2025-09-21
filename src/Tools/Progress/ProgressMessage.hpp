#ifndef ProgressMessage_hpp
#define ProgressMessage_hpp

#include "ProgressRange.hpp"

struct ProgressRangeView {
    ProgressRangeView(const ProgressRange& aRange) 
        : progressFraction(aRange.currentProgress()), 
          label(aRange.label()) {}
    
    Fraction progressFraction;
    std::string label;
};

class ProgressMessage {
public:
    explicit ProgressMessage(const ProgressRange& aRange)
        : progressRanges(getViewChainFromRange(aRange)) {}

    std::vector<ProgressRangeView> progressRanges;

private:
    static std::vector<ProgressRangeView> getViewChainFromRange(
        const ProgressRange& aRange
    ) {
        std::vector<ProgressRangeView> ranges;
        const ProgressRange* current = &aRange;

        while (current) {
            ranges.push_back(ProgressRangeView(*current));
            auto child = current->child();
            if (child) {
                current = &child->get();
            } else {
                current = nullptr;
            }
        }
        return ranges;
    }
};

#endif
