#ifndef DomainId_hpp
#define DomainId_hpp

#include "Dim.hpp"

class DomainId {
    public:
    DomainId(
        int aId, const Dim& aDim
    ) : mId(aId), mDim(aDim) {}

    static bool isValid(const DomainId& aDomainId) {
        return aDomainId.mId != -1;
    }
    static DomainId invalid() {return DomainId(-1, Dim::D3);}

    private:
    const int mId;
    const Dim mDim;
};

#endif