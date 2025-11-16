#ifndef DomainId_hpp
#define DomainId_hpp

#include <ostream>
#include <functional>

class DomainId {
public:
    DomainId() noexcept : mId(-1) {}
    explicit DomainId(int id) noexcept : mId(id) {}
    static DomainId invalid() {return DomainId();}


    [[nodiscard]] int value() const noexcept { return mId; }

    [[nodiscard]] bool valid() const noexcept { return mId >= 0; }

    bool operator==(const DomainId& other) const noexcept { return mId == other.mId; }
    bool operator!=(const DomainId& other) const noexcept { return mId != other.mId; }
    bool operator<(const DomainId& other) const noexcept { return mId < other.mId; }

    explicit operator int() const noexcept { return mId; }

private:
    int mId;
};

inline std::ostream& operator<<(std::ostream& os, const DomainId& id) {
    os << id.value();
    return os;
}

struct DomainIdHash {
    std::size_t operator()(const DomainId& id) const noexcept {
        return std::hash<int>{}(id.value());
    }
};

#endif // DomainId_hpp

