#ifndef SubShapeDomain_hpp
#define SubShapeDomain_hpp

#include "DomainId.hpp"
#include "Dim.hpp"

#include <vector>

class SubShapeDomain {
public:
    SubShapeDomain(
        DomainId aId,
        Dim aDim,
        std::vector<int> aSubIds
    )
        : mId(aId),
          mDim(aDim),
          mSubIds(std::move(aSubIds))
    {}

    virtual ~SubShapeDomain() = default;

    inline DomainId id() const { return mId; }
    inline Dim dim() const { return mDim; }

    inline const std::vector<int>& subShapeIds() const
    {
        return mSubIds;
    }

protected:
    const DomainId mId = DomainId::invalid();
    const Dim mDim = Dim::D3;
    std::vector<int> mSubIds;
};

class Domain1D : public SubShapeDomain {
public:
    Domain1D(DomainId aId, std::vector<int> aSubIds)
        : SubShapeDomain(aId, Dim::D1, std::move(aSubIds))
    {}
};

class Domain2D : public SubShapeDomain {
public:
    Domain2D(DomainId aId, std::vector<int> aSubIds)
        : SubShapeDomain(aId, Dim::D2, std::move(aSubIds))
    {}
};

class Domain3D : public SubShapeDomain {
public:
    Domain3D(DomainId aId, std::vector<int> aSubIds)
        : SubShapeDomain(aId, Dim::D3, std::move(aSubIds))
    {}
};

#endif
