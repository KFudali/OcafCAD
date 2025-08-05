#include "PartLabelKey.hpp"

#include <algorithm>

PartLabelKey::PartLabelKey(const std::vector<int>& aLabelTagList)
    : mLabelTagList(aLabelTagList) {}

PartLabelKey::PartLabelKey(const std::string& aLabelTagListString)
    : mLabelTagList(stringToTagList(aLabelTagListString)) {}

PartLabelKey::PartLabelKey(const TColStd_ListOfInteger& aOccListOfInteger)
    : mLabelTagList(occListToTagList(aOccListOfInteger)) {}

PartLabelKey::PartLabelKey(std::initializer_list<int> list)
    : mLabelTagList(list) {}

PartLabelKey::PartLabelKey(const PartLabelKey& aOther)
    : mLabelTagList(aOther.mLabelTagList) {}

PartLabelKey& PartLabelKey::operator=(const PartLabelKey& aOther) {
    if (this != &aOther) {
        mLabelTagList = aOther.mLabelTagList;
    }
    return *this;
}


bool PartLabelKey::operator==(const PartLabelKey& aOtherKey) const {
    return mLabelTagList == aOtherKey.mLabelTagList;
};

bool PartLabelKey::operator<(const PartLabelKey& aOtherKey) const {
    return mLabelTagList < aOtherKey.mLabelTagList;
};

std::vector<int> PartLabelKey::occListToTagList(
    const TColStd_ListOfInteger& aOccList) const {
    std::vector<int> result;
    result.reserve(aOccList.Extent());
    for (TColStd_ListOfInteger::Iterator it(aOccList); it.More(); it.Next()) {
        result.push_back(it.Value());
    }
    return result;
}

std::vector<int> PartLabelKey::stringToTagList(const std::string& str) const {
    std::vector<int> result;
    std::string token;
    std::istringstream iss(str);
    while (std::getline(iss, token, ':')) {
        if (!token.empty()) {
            result.push_back(std::stoi(token));
        }
    }
    return result;
}

std::string PartLabelKey::toString() const {
    if (mLabelTagList.empty()) return "";

    std::ostringstream oss;
    std::transform(mLabelTagList.begin(), mLabelTagList.end() - 1,
                   std::ostream_iterator<std::string>(oss, ":"),
                   [](int val) { return std::to_string(val); });

    oss << mLabelTagList.back();
    return oss.str();
}

std::vector<int> PartLabelKey::toStdVector() const { return mLabelTagList; };
TColStd_ListOfInteger PartLabelKey::toOccList() const {
    TColStd_ListOfInteger occTagList;
    for (const auto tag : mLabelTagList) {
        occTagList.Append(tag);
    }
    return occTagList;
};