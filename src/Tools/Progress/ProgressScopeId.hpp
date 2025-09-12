#ifndef ProgressScopeId_hpp
#define ProgressScopeId_hpp

#include <vector>
#include <memory>
#include <compare>
#include <algorithm>
#include <sstream>

class ProgressScopeId {
public:
    ProgressScopeId() = default;
    ProgressScopeId(std::vector<int> path) : _path(std::move(path)) {}

    ProgressScopeId spawnChild(int childIntKey) const {
        auto newPath = _path;
        newPath.push_back(childIntKey);
        return ProgressScopeId(std::move(newPath));
    }

    const std::vector<int>& path() const { return _path; }
    std::string toString() const {
    if (_path.empty()) {
        return "root";
    }

    std::ostringstream oss;
    std::transform(_path.begin(), _path.end(), 
                   std::ostream_iterator<int>(oss, "."),
                   [](int v) { return v; });

    std::string result = oss.str();
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}


    auto operator<=>(const ProgressScopeId&) const = default;



private:
    std::vector<int> _path;
};

#endif