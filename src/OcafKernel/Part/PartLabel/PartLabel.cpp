#include "PartLabel.hpp"
#include <sstream>
#include <algorithm>

#include <TNaming_NamedShape.hxx>

PartLabel::PartLabel(TDF_Label aLabel) : mLabel(aLabel){
    Handle(TNaming_NamedShape) namedShape;
    if (!aLabel.FindAttribute(TNaming_NamedShape::GetID(), namedShape)) {
        throw LabelDoesNotReferenceShape();
    }
}

std::vector<int> PartLabel::toIntVector() const {
    std::vector<int> result;
    TDF_Label currentLabel = mLabel;

    while (!currentLabel.IsNull()) {
        result.push_back(currentLabel.Tag());
        currentLabel = currentLabel.Father();
    }

    std::reverse(result.begin(), result.end());
    return result;
}


std::string PartLabel::toString() const {
    auto tagVector = toIntVector();
    if (tagVector.empty()) return "";

    std::ostringstream oss;
    std::transform(tagVector.begin(), tagVector.end() - 1,
                   std::ostream_iterator<std::string>(oss, ":"),
                   [](int val) { return std::to_string(val); });
    oss << tagVector.back();
    return oss.str();
}

