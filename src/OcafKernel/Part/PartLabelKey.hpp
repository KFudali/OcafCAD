#ifndef PartLabelKey_hpp
#define PartLabelKey_hpp

#include <TColStd_ListOfInteger.hxx>
#include <boost/functional/hash.hpp>
#include <string>
#include <vector>

class PartLabelKey {
   public:
    PartLabelKey(const std::vector<int>& aLabelTagList);
    PartLabelKey(const std::string& aLabelTagListString);
    PartLabelKey(const TColStd_ListOfInteger& aLabelTagListString);
    PartLabelKey(std::initializer_list<int> list);

    ~PartLabelKey() = default;

    PartLabelKey(const PartLabelKey& aOther);
    PartLabelKey& operator=(const PartLabelKey& aOther);

    bool operator==(const PartLabelKey& aOtherKey) const;
    bool operator<(const PartLabelKey& aOtherKey) const;

    std::string toString() const;
    std::vector<int> toStdVector() const;
    TColStd_ListOfInteger toOccList() const;

   private:
    std::vector<int> occListToTagList(
        const TColStd_ListOfInteger& aLabelTagListString) const;

    std::vector<int> stringToTagList(
        const std::string& aLabelTagListString) const;

    std::vector<int> mLabelTagList;
};

namespace std {
template <>
struct hash<PartLabelKey> {
    std::size_t operator()(const PartLabelKey& key) const {
        std::size_t seed = 0;
        const auto& tagList = key.toStdVector();
        boost::hash_range(seed, tagList.begin(), tagList.end());
        return seed;
    }
};
}  // namespace std

#endif