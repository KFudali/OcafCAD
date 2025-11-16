#ifndef DomainRegistry_hpp
#define DomainRegistry_hpp

#include "DomainId.hpp"
#include "Dim.hpp"

class DomainRegistry {
    public:
    DomainRegistry() = default;

    DomainId uniqueId(const Dim& aDim) {
        DomainId id(mNextId);
        ++mNextId;
        return id;
    }

    private: 
    int mNextId = 1;
};

#endif