#include "DocLabel.hpp"
#include <sstream>
#include <algorithm>

DocLabel::DocLabel(TDF_Label aLabel) : mLabel(aLabel){}

std::vector<int> DocLabel::toIntVector() const {
    std::vector<int> labelTagPath;
    TDF_Label currentLabel = mLabel;
    for (TDF_Label label = mLabel; !label.IsNull(); label = label.Father()) {
        labelTagPath.push_back(label.Tag());
    }    
    std::reverse(labelTagPath.begin(), labelTagPath.end());
    return labelTagPath;
}

std::string DocLabel::toString() const {
    auto tagVector = toIntVector();
    if (tagVector.empty()) return "";

    std::ostringstream oss;
    std::transform(tagVector.begin(), tagVector.end() - 1,
                   std::ostream_iterator<std::string>(oss, ":"),
                   [](int val) { return std::to_string(val); });
    oss << tagVector.back();
    return oss.str();
}


