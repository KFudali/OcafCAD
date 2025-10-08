#ifndef DocumentGeometryFixture_hpp
#define DocumentGeometryFixture_hpp

#include "StubOccDocument.hpp"
#include "StubPartPrototypes.hpp"
#include "DocumentGeometry.hpp"

class DocumentGeometryFixture {
    public:

    DocumentGeometryFixture() : mOccDoc(), mDocGeo(mOccDoc.doc()) {}
    DocumentGeometry& documentGeometry() return {mDocGeo;}

    private:
    StubOccDocument mOccDoc;
    DocumentGeometry mDocGeo;
};

#endif