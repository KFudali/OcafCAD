#ifndef ShapeDomainDescription_hpp
#define ShapeDomainDescription_hpp

#include "Shape.hpp"
#include "Dim.hpp"
#include "DomainId.hpp"
#include "SubSHapeDomain.hpp"
#include "PartSubShapeNamedSelection.hpp"

class ShapeDomainDescription {
    public:
    ShapeDomainDescription() = default;

    bool addDomain(const SubShapeDomain& aDomain);    
    bool addDomain1D(const Domain1D& aDomainDescription);
    bool addDomain2D(const Domain2D& aDomainDescription);
    bool addDomain3D(const Domain3D& aDomainDescription);
    
    std::vector<DomainId> namedDomains(const Dim& aDim) const;
    
    DomainId edgeDomain(int aSubEdgeId) const;
    DomainId faceDomain(int aSubFaceId) const;
    DomainId volumeDomain(int aVolumeId) const;
    
    private:
    std::unordered_map<int, DomainId> mEdgeDomains;
    std::unordered_map<int, DomainId> mFaceDomains;
    std::unordered_map<int, DomainId> mVolumeDomains;

    std::unordered_map<DomainId, std::vector<int>, DomainIdHash> mDomainEdges;
    std::unordered_map<DomainId, std::vector<int>, DomainIdHash> mDomainFaces;
    std::unordered_map<DomainId, std::vector<int>, DomainIdHash> mDomainVolumes;
};

#endif