#ifndef DocumentGeometryFixture_hpp
#define DocumentGeometryFixture_hpp

#include <gmock/gmock.h>
#include <memory>
#include "StubOccDocument.hpp"
#include "StubPartPrototypes.hpp"
#include "DocumentGeometry.hpp"

class DocumentGeometryFixture : public ::testing::Test {
    protected:
    void SetUp() {
        geoDoc = std::make_unique<DocumentGeometry>(mOccDoc.doc());
    }
    std::unique_ptr<DocumentGeometry> geoDoc;

    private:
    StubOccDocument mOccDoc;
};

#endif