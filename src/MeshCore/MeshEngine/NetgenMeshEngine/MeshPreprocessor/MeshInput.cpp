#include "MeshInput.hpp"

bool MeshInput::applyNamedSelection() {
    
    mNetgenGeometry->BuildFMap();
    netgen::MeshingParameters params{};

    auto& face = mNetgenGeometry->fmap(1);
    mNetgenGeometry->GetFace(face).properties.name = std::string("labeledFace");
    auto& anotherFace = mNetgenGeometry->fmap(2);
    mNetgenGeometry->GetFace(anotherFace).properties.name = std::string("labeledFace");
    


    // mNetgenGeometry->GetFace(face).RestrictH():
    mNetgenGeometry->GenerateMesh(mNetgenMesh, params);
    for (int i = 1; i <= mNetgenMesh->GetNFD(); ++i) {
        const netgen::FaceDescriptor& fd = mNetgenMesh->GetFaceDescriptor(i);
        std::cout << "Face " << i
                  << "  surfnr=" << fd.SurfNr()
                  << "  bcprop=" << fd.BCProperty()
                  << "  bcName=" << fd.GetBCName()
                  << std::endl;
    }
    return true;
}