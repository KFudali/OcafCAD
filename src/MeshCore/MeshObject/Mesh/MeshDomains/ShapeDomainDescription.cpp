#include "ShapeDomainDescription.hpp"

bool ShapeDomainDescription::addDomain(const SubShapeDomain& aDomain)
{
    switch (aDomain.dim()) {
        case Dim::D1:
            return addDomain1D(static_cast<const Domain1D&>(aDomain));

        case Dim::D2:
            return addDomain2D(static_cast<const Domain2D&>(aDomain));

        case Dim::D3:
            return addDomain3D(static_cast<const Domain3D&>(aDomain));

        default:
            return false;
    }
}

bool ShapeDomainDescription::addDomain1D(const Domain1D& aDomain)
{
    const DomainId id = aDomain.id();
    for (int edgeId : aDomain.subShapeIds()) {
        mEdgeDomains[edgeId] = id;
        mDomainEdges[id].push_back(edgeId);
    }

    return true;
}

bool ShapeDomainDescription::addDomain2D(const Domain2D& aDomain)
{
    const DomainId id = aDomain.id();
    for (int faceId : aDomain.subShapeIds()) {
        mFaceDomains[faceId] = id;
        mDomainFaces[id].push_back(faceId);
    }

    return true;
}

bool ShapeDomainDescription::addDomain3D(const Domain3D& aDomain)
{
    const DomainId id = aDomain.id();
    for (int volId : aDomain.subShapeIds()) {
        mVolumeDomains[volId] = id;
        mDomainVolumes[id].push_back(volId);
    }

    return true;
}

std::vector<DomainId> ShapeDomainDescription::namedDomains(
    const Dim& aDim
) const
{
    std::vector<DomainId> result;
    switch (aDim) {
        case Dim::D1:
            for (const auto& kv : mDomainEdges)
                result.push_back(kv.first);
            break;
        case Dim::D2:
            for (const auto& kv : mDomainFaces)
                result.push_back(kv.first);
            break;
        case Dim::D3:
            for (const auto& kv : mDomainVolumes)
                result.push_back(kv.first);
            break;
        default:
            break;
    }
    return result;
}
DomainId ShapeDomainDescription::edgeDomain(int aSubEdgeId) const
{
    auto it = mEdgeDomains.find(aSubEdgeId);
    if (it != mEdgeDomains.end())
        return it->second;

    return DomainId::invalid();
}

DomainId ShapeDomainDescription::faceDomain(int aSubFaceId) const
{
    auto it = mFaceDomains.find(aSubFaceId);
    if (it != mFaceDomains.end())
        return it->second;

    return DomainId::invalid();
}

DomainId ShapeDomainDescription::volumeDomain(int aVolumeId) const
{
    auto it = mVolumeDomains.find(aVolumeId);
    if (it != mVolumeDomains.end())
        return it->second;

    return DomainId::invalid();
}
